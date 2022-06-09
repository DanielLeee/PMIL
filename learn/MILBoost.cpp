#include "MILBoost.h"

MILBoost::MILBoost(string parafile)
{
	CConfigFile config(parafile);
	//Boost Para
	T = config.read<int>("NUM_WEAK_CLF");
	n_bins = config.read<int>("NUM_BINS");
	alpha_bound = config.read<double>("ALPHA_BOUND");
	alpha_bins = config.read<int>("ALPHA_BINS");
	//weak classifier
	Clf::parameter(config);
	//file
	clf_file = Expr::model_dir + config.read<string>("CLF");
	log_file = Expr::model_dir + config.read<string>("LOG");
	log_fout = NULL;
	//feature
	FILE* fin = fopen(Expr::feature_file.c_str(), "r");		
	fscanf(fin, "%*[^\n]\n");
	char name[MAX_PATH];
	int left, right;
	while (fscanf(fin, "%s : %d to %d", name, &left, &right) == 3)
		for (int i = left; i <= right; ++i)
			feature.push_back(Feature(name));
	fclose(fin);
}

void MILBoost::softmax(double& a, double b)
{
	a = 1 - (1 - a) * (1 - b);
}

void MILBoost::train(const Data* neg, const Data* pos)
{	
	const Data* data[2] = {neg, pos};
	if (Parallel::rank == 0)
		log_fout = fopen(log_file.c_str(), "w");	
	// Calc # of inst & bag		
	int pos_inst = pos->NInst, neg_inst = neg->NInst;
	int pos_bag = pos->NBag, neg_bag = neg->NBag;
	int n = pos_inst + neg_inst, N = pos_bag + neg_bag, m = feature.size();
	MPI_Allreduce(&pos_inst, Parallel::n + 1, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&neg_inst, Parallel::n, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&pos_bag, Parallel::N + 1, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);	
	MPI_Allreduce(&neg_bag, Parallel::N, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);	
	print("%d features\n", m);
	print("%d(%d+/%d-) bags\n", Parallel::N[0] + Parallel::N[1], Parallel::N[1], Parallel::N[0]);
	print("%d(%d+/%d-) insts\n", Parallel::n[0] + Parallel::n[1], Parallel::n[1], Parallel::n[0]);
	// Calc feature bound	
	for (int p = 0; p < 2; ++p)
		for (int i = 0; i < data[p]->NInst; ++i)
			for (int j = 0; j < m; ++j) {
				double val = (*data[p])(i, j);
				if (val < feature[j].lower)
					feature[j].lower = val;
				if (val > feature[j].upper)
					feature[j].upper = val;
			}
	for (int i = 0; i < m; ++i) {
		Parallel::bufd[i] = feature[i].lower;
		Parallel::bufd[i + m] = feature[i].upper;
	}
	MPI_Allreduce(Parallel::bufd, Parallel::bufd + 2 * m, m, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
	MPI_Allreduce(Parallel::bufd + m, Parallel::bufd + 3 * m, m, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
	for (int i = 0; i < m; ++i) {
		feature[i].lower = Parallel::bufd[i + 2 * m];
		feature[i].upper = Parallel::bufd[i + 3 * m];		
		feature[i].n_bins = n_bins;			
	}
	// Learn
	print("Train for %d iterations\n", T);	
	vector<double> h[2], dh[2], w[2];
	h[0].assign(neg_inst, 0);
	h[1].assign(pos_inst, 0);
	dh[0].assign(neg_inst, 0);
	dh[1].assign(pos_inst, 0);
	w[0].assign(neg_inst, 0);
	w[1].assign(pos_inst, 0);
	clear();
	for (int t = 0; t < T; ++t) {
		//Update weight	
		vector<double> P(pos_bag, 0);
		for (int i = 0; i < neg_inst; ++i)
			w[0][i] = -sigmoid(h[0][i]);
		for (int i = 0; i < pos_inst; ++i)
			softmax(P[pos->bag[i]], (w[1][i] = sigmoid(h[1][i])));
		for (int i = 0; i < pos_inst; ++i)
			w[1][i] *= (1 - P[pos->bag[i]]) / (P[pos->bag[i]] + eps);
		//Calc val hist of weight
		vector< vector<double> > hist(m, vector<double>(n_bins, 0));
		for (int p = 0; p < 2; ++p)
			for (int i = 0; i < data[p]->NInst; ++i) {
				double *ptr = (*data[p])(i);
				for (int j = 0; j < m; ++j)
					hist[j][feature[j].index(ptr[j])] += w[p][i];
			}
		for (int i = 0; i < m; ++i) {
			MPI_Allreduce(&hist[i][0], Parallel::bufd, n_bins, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);	
			memcpy(&hist[i][0], Parallel::bufd, n_bins * sizeof(double));
		}
		//Find best weak clf
		Clf* clf = Clf::train_global(hist, feature);
		assert(clf != NULL);
		//Find best alpha
		for (int p = 0; p < 2; ++p)
			for (int i = 0; i < data[p]->NInst; ++i)				
				dh[p][i] = (*clf)((*data[p])(i));
		double best_alpha, best_L = inf;
		double lef = 0, rig = 1;
		while (lef + alpha_bound < rig) {			
			double step = (rig - lef) / alpha_bins, a = lef;
			vector<double> va, vL;
			while ((a += step) < rig) {
				vector<double> P[2];
				P[0].assign(neg_bag, 0);
				P[1].assign(pos_bag, 0);				
				for (int p = 0; p < 2; ++p)
					for (int i = 0; i < data[p]->NInst; ++i)
						softmax(P[p][data[p]->bag[i]], sigmoid(h[p][i] + a * dh[p][i]));
				double L[2] = {0, 0};		
				for (int i = 0; i < neg_bag; ++i)
					L[0] -= log(1 - P[0][i] + eps);
				for (int i = 0; i < pos_bag; ++i)
					L[1] -= log(P[1][i] + eps);
				va.push_back(a);
				vL.push_back(L[0] / Parallel::N[0] + L[1] / Parallel::N[1]);
			}
			MPI_Allreduce(&vL[0], Parallel::bufd, vL.size(), MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
			for (int i = 0; i < vL.size(); ++i)
				if (Parallel::bufd[i] < best_L) {
					best_alpha = va[i];
					best_L = Parallel::bufd[i];
				}
			lef = best_alpha - step;
			rig = best_alpha + step;
			if (lef < 0)
				lef = 0;
			if (rig > 1)
				rig = 1;
		}
		clf->alpha = best_alpha;
		weak_clf.push_back(clf);
		//update h
		for (int p = 0; p < 2; ++p)
			for (int i = 0; i < data[p]->NInst; ++i)
				h[p][i] += best_alpha * dh[p][i];
		//log
		print("%4d : Loss=%.5lf %s\n", t, best_L, clf->to_str());
		++feature[clf->idx].times;
		feature[clf->idx].weight += best_alpha;				
	}	
	print("Training finished\n");
	map<string, pair<int, double> > F;	
	for (int i = 0; i < feature.size(); ++i) {
		if (feature[i].times > 0)
			print("Ftr%d [%.5lf, %.5lf] times=%d weight=%.5lf\n", i, feature[i].lower, feature[i].upper, feature[i].times, feature[i].weight);
		F[feature[i].name].first += feature[i].times;
		F[feature[i].name].second += feature[i].weight;
	}
	for (map<string, pair<int, double> >::iterator it = F.begin(); it != F.end(); ++it)
		print("%s times=%d weight=%.5lf\n", it->first.c_str(), it->second.first, it->second.second);
}

void MILBoost::test(const Data* data, Result &res)
{
	vector<double> P(data->NBag, 0);
	vector< map< pair<int, int>, double> > p(data->NBag);
	for (int i = 0; i < data->NInst; ++i) {
		double h = 0;
		for (int j = 0; j < weak_clf.size(); ++j)
			h += (*weak_clf[j])((*data)(i));
		softmax(P[data->bag[i]], sigmoid(h));
		softmax(p[data->bag[i]][data->pos[i]], sigmoid(h));				
	}	
	for (int i = 0; i < P.size(); ++i) {
		res.bag.push_back(P[i]);
		res.inst.push_back(vector<Result::Patch>());
		for (map< pair<int, int>, double>::iterator it = p[i].begin(); it != p[i].end(); ++it)
			res.inst[i].push_back(Result::Patch(it->first.first, it->first.second, it->second));
	}
}

int MILBoost::print(const char* format, ...)
{
	if (Parallel::rank != 0)
		return 0;
	SYSTEMTIME sys; 
	GetLocalTime(&sys); 	
	va_list arg;
	va_start(arg, format);
	int ret = 0;
	ret += fprintf(log_fout, "[%02d/%02d %02d:%02d:%02d] ", sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond); 
	ret += vfprintf(log_fout, format, arg);	
	fflush(log_fout);
	va_end(arg);
	return ret;
}

void MILBoost::to_file()
{
	if (Parallel::rank != 0) 
		return;
	FILE* fout = fopen(clf_file.c_str(), "w");
	for (int i = 0; i < weak_clf.size(); ++i)
		fprintf(fout, "%s\n", (*weak_clf[i]).to_str(true));
	fclose(fout);
}

void MILBoost::from_file()
{
	FILE* fin = fopen(clf_file.c_str(), "r");
	char buf[MAX_PATH];
	clear();
	while (fscanf(fin, "%[^\n]\n", buf) == 1) {
		Clf* clf = Clf::from_str_global(buf);
		if (clf != NULL)
			weak_clf.push_back(clf);
	}
	fclose(fin);
}

void MILBoost::clear()
{
	for (int i = 0; i < weak_clf.size(); ++i)
		delete weak_clf[i];
	weak_clf.clear();
}

MILBoost::~MILBoost()
{
	clear();
	if (log_fout != NULL)
		fclose(log_fout);
}
