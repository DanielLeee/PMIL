#include "Common.h"
#ifdef _DEBUG
#pragma comment(lib, "commond.lib")
#else
#pragma comment(lib, "common.lib")
#endif

int _main(int argc, char **argv)
{
	MPI_Comm_size(MPI_COMM_WORLD, &Parallel::size);
	MPI_Comm_rank(MPI_COMM_WORLD, &Parallel::rank);



	return 0;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);	
	MPI_Finalize();	
	return 0;
}
