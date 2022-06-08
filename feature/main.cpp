#include "config.h"
#include "Feature.h"

void gen(int start, int end, int testStep, int trainStep, vector< pair<int, bool> >& ret)
{
	ret.clear();
	ret.push_back(make_pair(start, true));
	int last = start;
	do {
		start += testStep - int((end - start) % testStep > 0);
		if (start > end)
			start = end;
		ret.push_back(make_pair(start, start - last >= trainStep - 1));
		if (start - last >= trainStep - 1)
			last = start;
	}while (start != end);	
}

int get_feature(CFeature &cf, const Mat& img, FILE* fout)
{		
	//init	
	if (!img.data)
		return -1;
	int H = img.rows;
	int W = img.cols;	
	int size = cf.m_patchSize;
	if (W < size || H < size)
		return -1;	
	int testStep = cf.m_testStep;
	int trainStep = cf.m_trainStep;	
	int nF = cf.GetFeatureLength();						
	//gen h & w	
	vector< pair<int, bool> > vh, vw;
	gen(0, H - size, testStep, trainStep, vh);
	gen(0, W - size, testStep, trainStep, vw);
	//compute
	for (int ih = 0; ih < vh.size(); ++ih)
		for (int iw = 0; iw < vw.size(); ++iw) {
			int top = vh[ih].first, left = vw[iw].first;
			float *features = cf.GetFeatures(img(Range(top, top + size), Range(left, left + size)));
			fprintf(fout, "%s %d %d", (vh[ih].second && vw[iw].second) ? "train" : "test", top + size / 2, left + size / 2);
			for (int j = 0; j < nF; ++j) 
				fprintf(fout, " %d:%.8f", j, features[j]);
			fprintf(fout, "\n");			
			delete[] features;
			features = cf.GetFeatures(img(Range(top + size / 4, top + size - size / 4), Range(left + size / 4, left + size - size / 4)));
			fprintf(fout, "%s %d %d", (vh[ih].second && vw[iw].second) ? "train" : "test", top + size / 2, left + size / 2);
			for (int j = 0; j < nF; ++j) 
				fprintf(fout, " %d:%.8f", j, features[j]);
			fprintf(fout, "\n");			
			delete[] features;
			if (top - size / 2 < 0 || top + size + size / 2 >= H)
				continue;
			if (left - size / 2 < 0 || left + size + size / 2 >= W)
				continue;
			features = cf.GetFeatures(img(Range(top - size / 2, top + size + size / 2), Range(left - size / 2, left + size + size /2)));
			fprintf(fout, "%s %d %d", (vh[ih].second && vw[iw].second) ? "train" : "test", top + size / 2, left + size / 2);
			for (int j = 0; j < nF; ++j) 
				fprintf(fout, " %d:%.8f", j, features[j]);
			fprintf(fout, "\n");
			delete[] features;			
		}
	return 0;
}

void _main(int argc, char **argv)
{
	if (argc != 2) {
		cerr << "mpiexec feature.exe expr.para" << endl;		
		return;
	}
	Tools::InitExpr(argv[1]);
	CFeature cf(Expr::feature_para);

	vector<string> list = Tools::ListDir(Expr::image_dir, "*." + Expr::image_ext);	
	if (Parallel::rank == 0)
		Tools::CreateDirs(Expr::feature_dir, list, true);		
	MPI_Barrier(MPI_COMM_WORLD);

	Mat img;
	FILE* fout;
	char buf[MAX_PATH];
	int ret;
	for (int i = 0; i < list.size(); i += Parallel::size) {
		for (int j = 0; j < Parallel::size && i + j < list.size(); ++j) {
			if ((j + 1) % Expr::IO_limit == 0) 
				MPI_Barrier(MPI_COMM_WORLD);
			if ((i + j) % Parallel::size == Parallel::rank) {
				printf("Process %d reading image %s\n", Parallel::rank, list[i + j].c_str()); 
				fflush(stdout);
				img = imread(Expr::image_dir + list[i + j] + "." + Expr::image_ext);
			}
		}
		for (int j = 0; j < Parallel::size && i + j < list.size(); ++j) 
			if ((i + j) % Parallel::size == Parallel::rank) {
				printf("Process %d computing image %s\n", Parallel::rank, list[i + j].c_str()); 
				fflush(stdout);
				sprintf(buf, "%s%d_feature", Expr::cache_dir.c_str(), Parallel::rank);
				fout = fopen(buf, "w");
				ret = get_feature(cf, img, fout);
				if (ret != 0) {
					printf("Process %d failed in %dx%d image %s\n", Parallel::rank, img.cols, img.rows, list[i + j].c_str());
					fflush(stdout);
				}
				fclose(fout);
			}
		for (int j = 0; j < Parallel::size && i + j < list.size(); ++j) {
			if ((j + 1) % Expr::IO_limit == 0) 
				MPI_Barrier(MPI_COMM_WORLD);
			if ((i + j) % Parallel::size == Parallel::rank && ret == 0) {
				printf("Process copying data\n", Parallel::rank); 
				fflush(stdout);
				Tools::copy(buf, Expr::feature_dir + list[i + j] + "." + Expr::feature_ext);
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);

	if (Parallel::rank == 0) {
		list = Tools::ListDir(Expr::feature_dir, "*." + Expr::feature_ext);		
		FILE *trainFile, *testFile;
		trainFile = fopen(Expr::train_chunk_file.c_str(), "w");
		testFile = fopen(Expr::test_chunk_file.c_str(), "w");
		if (cf.m_trainRate == 100 && cf.m_testRate == 100) {
			for (int i = 0; i < list.size(); ++i) {
				fprintf(trainFile, "%s\n", list[i].c_str());
				fprintf(testFile, "%s\n", list[i].c_str());
			}
		}else {
			for (int i = list.size() - 1; i > 0; --i)
				swap(list[i], list[rand() * rand() % i]);
			int test = cf.m_testRate * list.size() / 100;		
			for (int i = 0; i < test; ++i)
				if (i >= 0 && i < list.size())
					fprintf(testFile, "%s\n", list[i].c_str());
			reverse(list.begin(), list.end());
			int train = cf.m_trainRate * list.size() / 100;
			for (int i = 0; i < train; ++i) 
				if (i >= 0 && i < list.size())
					fprintf(trainFile, "%s\n", list[i].c_str());
		}					
		fclose(trainFile);
		fclose(testFile);		
	}
	MPI_Barrier(MPI_COMM_WORLD);
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);	
	MPI_Finalize();	
	return 0;
}
