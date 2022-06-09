#include "Common.h"
#ifdef _DEBUG
#pragma comment(lib, "commond.lib")
#else
#pragma comment(lib, "common.lib")
#endif

const int N = 1000, M = 50, D = 100;
FILE* feature;

void (*gen)(FILE* fout, int id, bool pos);

void linear(FILE* fout, int id, bool pos)
{
	static double d[D], a[D];
	static bool init = false;
	if (!init) {
		init = true;
		for (int i = 0; i < D; ++i) {
			d[i] = log(double(rand() + 1));
			if (rand() % 2 == 0)
				d[i] = -d[i];
		}		
		for (int i = 0; i < D; ++i)
			fprintf(feature, "F_%.3lf : %d to %d\n", d[i], i, i);
	}
	double s = 0;
	for (int i = 0; i < D; ++i) {
		a[i] = rand() % 31 - 15;
		s += a[i] * d[i];
	}
	if ((s > 0) != pos)
		gen(fout, id, pos);
	else {
		fprintf(fout, "train %d %s", id, pos ? "1" : "-1");
		for (int i = 0; i < D; ++i)
			fprintf(fout, " %d:%.0lf", i, a[i]);
		fprintf(fout, "\n");
	}
}

void circle(FILE* fout, int id, bool pos)
{
	static double a[D];
	static int M = 1000, R = D * M * M / 3;
	static bool init = false;
	if (!init) {
		init = true;
		fprintf(feature, "F : %d to %d\n", 0, D - 1);			
	}
	double s = 0;
	for (int i = 0; i < D; ++i) {
		a[i] = rand() % M;
		s += a[i] * a[i];
	}
	if ((s <= R) != pos)
		gen(fout, id, pos);
	else {
		fprintf(fout, "train %d %s", id, pos ? "1" : "-1");
		for (int i = 0; i < D; ++i)
			fprintf(fout, " %d:%.0lf", i, a[i]);
		fprintf(fout, "\n");
	}
}

void xor(FILE* fout, int id, bool pos)
{	
	static double d[D], a[D];
	static bool init = false;
	if (!init) {
		init = true;
		for (int i = 0; i < D; ++i) {
			d[i] = rand();
			if (rand() % 2 == 0)
				d[i] = -d[i];
		}		
		for (int i = 0; i < D; ++i)
			fprintf(feature, "F_%.3lf : %d to %d\n", d[i], i, i);
	}
	bool p = true;
	for (int i = 0; i < D; ++i) {
		a[i] = rand();
		if (rand() % 2 == 0)
			a[i] = -a[i];
		if (a[i] > d[i])
			p = !p;		
	}
	if (p != pos)
		gen(fout, id, pos);
	else {
		fprintf(fout, "train %d %s", id, pos ? "1" : "-1");
		for (int i = 0; i < D; ++i)
			fprintf(fout, " %d:%.0lf", i, a[i]);
		fprintf(fout, "\n");
	}
}

void polynomial(FILE* fout, int id, bool pos)
{
	static int M = 32768;
	static double x[D], a[D], b[D];
	static int e[D];
	static bool init = false;
	if (!init) {
		init = true;
		for (int i = 0; i < D; ++i) {
			a[i] = log(double(rand() + 1));
			b[i] = 1.5 * (rand() - rand()) / M;
			e[i] = rand() % (rand() % 10 + 1) + 1;
		}		
		for (int i = 0; i < D; ++i)
			fprintf(feature, "F_%.3lf_%.0lf_%d : %d to %d\n", a[i], b[i], e[i], i, i);
	}
	double s = 0;
	for (int i = 0; i < D; ++i) {
		x[i] = 1.5 * (rand() - rand()) / M;
		s += a[i] * pow(x[i] - b[i], e[i]);
	}
	if ((s > 0) != pos)
		gen(fout, id, pos);
	else {
		fprintf(fout, "train %d %s", id, pos ? "1" : "-1");
		for (int i = 0; i < D; ++i)
			fprintf(fout, " %d:%.9lf", i, x[i]);
		fprintf(fout, "\n");
	}
}

void sin_sum(FILE* fout, int id, bool pos)
{	
	static double x[D], a[D];
	static bool init = false;
	if (!init) {
		init = true;
		for (int i = 0; i < D; ++i) 
			a[i] = log(double(rand() + 1));				
		for (int i = 0; i < D; ++i)
			fprintf(feature, "F_%.3lf : %d to %d\n", a[i], i, i);
	}
	double s = 0;
	for (int i = 0; i < D; ++i) {
		x[i] = rand();
		s += a[i] * sin(x[i]);		
	}
	if ((s > 0) != pos)
		gen(fout, id, pos);
	else {
		fprintf(fout, "train %d %s", id, pos ? "1" : "-1");
		for (int i = 0; i < D; ++i)
			fprintf(fout, " %d:%.0lf", i, x[i]);
		fprintf(fout, "\n");
	}
}

int _main(int argc, char **argv)
{
	gen = polynomial;
	srand(time(NULL));
	Tools::InitExpr(argv[1]);
	
	FILE* train = fopen(Expr::train_chunk_file.c_str(), "w");
	FILE* test = fopen(Expr::test_chunk_file.c_str(), "w");	
	feature = fopen(Expr::feature_file.c_str(), "w");
	fprintf(feature, "Feature Total Length: %d\n", D);
	
	Tools::CreateDir(Expr::feature_dir + "pos");
	Tools::CreateDir(Expr::feature_dir + "neg");
	Tools::CreateDir(Expr::feature_dir + "test_pos");
	Tools::CreateDir(Expr::feature_dir + "test_neg");
	for (int i = 0; i < N; ++i) {		
		char buf[MAX_PATH];
		sprintf(buf, "%spos\\%d.dat", Expr::feature_dir.c_str(), i);
		FILE *fout = fopen(buf, "w");		
		for (int i = 1; i <= M; ++i)
			gen(fout, i, rand() % i == 0);		
		fclose(fout);
		fprintf(train, "%s\n", Tools::unext(string(buf)).c_str() + Expr::feature_dir.size());
	}
	for (int i = 0; i < N; ++i) {		
		char buf[MAX_PATH];
		sprintf(buf, "%sneg\\%d.dat", Expr::feature_dir.c_str(), i);
		FILE *fout = fopen(buf, "w");		
		for (int i = 1; i <= M; ++i)
			gen(fout, i, false);		
		fclose(fout);
		fprintf(train, "%s\n", Tools::unext(string(buf)).c_str() + Expr::feature_dir.size());
	}
	for (int i = 0; i < N; ++i) {		
		char buf[MAX_PATH];
		sprintf(buf, "%stest_pos\\%d.dat", Expr::feature_dir.c_str(), i);
		FILE *fout = fopen(buf, "w");		
		for (int i = 1; i <= M; ++i)
			gen(fout, i, rand() % i == 0);		
		fclose(fout);
		fprintf(test, "%s\n", Tools::unext(string(buf)).c_str() + Expr::feature_dir.size());
	}
	for (int i = 0; i < N; ++i) {		
		char buf[MAX_PATH];
		sprintf(buf, "%stest_neg\\%d.dat", Expr::feature_dir.c_str(), i);
		FILE *fout = fopen(buf, "w");		
		for (int i = 1; i <= M; ++i)
			gen(fout, i, false);		
		fclose(fout);
		fprintf(test, "%s\n", Tools::unext(string(buf)).c_str() + Expr::feature_dir.size());
	}	

	fclose(train);
	fclose(test);
	fclose(feature);

	return 0;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);
	MPI_Finalize();		
	return 0;
}
