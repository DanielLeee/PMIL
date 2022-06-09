#include "config.h"
#include "Solver.h"
#include "Roc.h"

Solver *sol;

bool positive(string s)
{				
	/*
	int x[] = {3,4,5,9,10,13,14,15,18,20,21,22,23,24,27,28,33,34,40,
41,42,45,56,66,67,69,73,74,76,78,84,85,86,87,90,91,94,
95,97,101,102,103,106,107,108,109,110,112,114,115,116,
123,125,128,132,133,136,144,146,150,159,163,165,168,
170,172,178,180,187,188,192,193,194,195,200,204,205,
208,211,214,219,221,223,226,229,232,234,235,236,239,
241,244,245,246,248,250,0};
	int id;
	sscanf(s.c_str(), "%d_", &id);
	for (int i = 0; x[i]; ++i)
		if (id == x[i])
			return true;
	return false;	
	*/
	return s.find("pos") != string::npos;
}

void train_model(string paraFile)
{
	MPI_Barrier(MPI_COMM_WORLD);
	sol = new Solver(paraFile);
	vector<string> list;
	FILE *chunk = fopen(Expr::train_chunk_file.c_str(), "r");
	char buf[MAX_PATH];
	while (fscanf(chunk, "%[^\n]\n", buf) == 1)
		list.push_back(string(buf));			
	fclose(chunk);
	for (int i = 0; i < list.size(); ++i) {
		if (i % Parallel::size == Parallel::rank)
			sol->load(Expr::feature_dir + list[i] + "." + Expr::feature_ext, positive(list[i]) ? Solver::POS : Solver::NEG);
		if (i % Expr::IO_limit == 0)
			MPI_Barrier(MPI_COMM_WORLD);
	}
	sol->train();
	MPI_Barrier(MPI_COMM_WORLD);
}

void predict(string paraFile)
{	
	MPI_Barrier(MPI_COMM_WORLD);
	if (sol == NULL) 
		sol = new Solver(paraFile);
	vector<string> list;
	FILE *chunk = fopen(Expr::test_chunk_file.c_str(), "r");
	char buf[MAX_PATH];
	while (fscanf(chunk, "%[^\n]\n", buf) == 1)
		list.push_back(string(buf));
	fclose(chunk);	
	sol->clear();
	for (int i = 0; i < list.size(); ++i) {
		if (i % Parallel::size == Parallel::rank)
			sol->load(Expr::feature_dir + list[i] + "." + Expr::feature_ext, Solver::TEST);
		if (i % Expr::IO_limit == 0)
			MPI_Barrier(MPI_COMM_WORLD);
	}
	Result res;
	sol->test(res);
	if (Parallel::rank == 0)
		Tools::CreateDirs(Expr::resultData_dir, list, true);
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i = 0, idx = 0; i < list.size(); ++i) {
		if (i % Parallel::size == Parallel::rank) {
			FILE* fout = fopen((Expr::resultData_dir + list[i] + "." + Expr::result_ext).c_str(), "w");
			fprintf(fout, "bag %.9lf\n", res.bag[idx]);
			for (int j = 0; j < res.inst[idx].size(); ++j) {
				Result::Patch &p = res.inst[idx][j];
				fprintf(fout, "(%d,%d) %.9lf\n", p.x, p.y, p.score);
			}
			fclose(fout);
			++idx;
		}			
		if (i % Expr::IO_limit == 0)
			MPI_Barrier(MPI_COMM_WORLD);
	}
	if (Parallel::rank == 0) {
		vector<double> score(list.size());
		for (int i = 0, idx = 0; i < list.size(); i += Parallel::size)
			score[i] = res.bag[idx++];
		for (int i = 1; i < Parallel::size; ++i) {
			int l = (list.size() - i + Parallel::size - 1) / Parallel::size;
			if (l == 0)
				continue;
			MPI_Recv(Parallel::bufd, l, MPI_DOUBLE, i, i, MPI_COMM_WORLD, Parallel::status);
			for (int j = i, idx = 0; j < list.size(); j += Parallel::size)
				score[j] = Parallel::bufd[idx++];
		}
		Roc roc;
		for (int i = 0; i < list.size(); ++i)
			roc.add(list[i], score[i], positive(list[i]));		
		FILE* fout = fopen(Expr::result_file.c_str(), "w");
		roc.find_thr(fout, Expr::roc_step);
		fprintf(fout, "\n");
		roc.calculate(fout);
		fprintf(fout, "\n");		
		roc.all_sample(fout);
		fclose(fout);
	}else 
		if (!res.bag.empty())
			MPI_Send(&(res.bag[0]), res.bag.size(), MPI_DOUBLE, 0, Parallel::rank, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
}

void _main(int argc, char **argv)
{	
	if (argc != 2 && argc != 3) {
		cerr << "mpiexec learn.exe expr.para -[train|test|all]" << endl;		
		return;
	}
	Tools::InitExpr(argv[1]);

	bool train = true, test = true;
	if (argc == 3) {
		if (strcmp(argv[2], "-train") == 0)
			test = false;
		if (strcmp(argv[2], "-test") == 0)
			train = false;
	}	
	if (train) 
		train_model(Expr::learn_para);		
	if (test)
		predict(Expr::learn_para);
	if (sol != NULL)
		delete sol;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);
	MPI_Finalize();	
	return 0;
}
