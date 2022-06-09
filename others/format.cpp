#include "Common.h"
#ifdef _DEBUG
#pragma comment(lib, "commond.lib")
#else
#pragma comment(lib, "common.lib")
#endif

char mask(string x)
{
	static string pos = "HLMDRYAOBT";
	for (int i = 0; i < x.size(); ++i) {
		char c = x[i];
		if (c >= 'a' && c <= 'z')
			c = c - 'a' + 'A';
		if (pos.find(c) != string::npos)
			return '1';
	}
	return '0';
}

int _main(int argc, char **argv)
{
	MPI_Comm_size(MPI_COMM_WORLD, &Parallel::size);
	MPI_Comm_rank(MPI_COMM_WORLD, &Parallel::rank);
	
	FILE *fin = fopen("a.txt", "r"), *fout = fopen("b.txt", "w"), *err = fopen("c.txt", "w");
	char buf[1000];
	string f1, f2, t;
	while (fscanf(fin, "%[^\n]\n", buf) == 1) {		
		if (buf[0] == '!') 
			if (buf[1] == '!')
				f2 = string(buf + 2);
			else
				f1 = string(buf + 1);
		else {
			t = string(buf);
			for (int i = t.size() - 4; i >= 0; --i)
				if (t.substr(i, 4) == ".jpg") {
					string tt = f1 + "\\" + f2 + "\\" + t.substr(0, i + 4);
					fprintf(_access(tt.c_str(), 0) ? err : fout, "%s %c\n", tt.c_str(), mask(t.substr(i + 4)));
					break;
				}
		}
	}	
	fclose(fin);
	fclose(fout);
	fclose(err);
	
	return 0;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);	
	MPI_Finalize();	
	return 0;
}
