#include <mpi.h>
#include <fstream>
#include <iostream>
#include <limits> //optional helper header
#include "Matrix.h"

double matrix_max(const Matrix & M){
	//--------YOUR matrix_max CODE BEGINS HERE (optional helper function)---------
	double max = M.getElem(0,0);

	for (size_t i = 0; i < M.getNcols(); i++)
	{
		for (size_t j = 0; j < M.getNrows(); j++)
		{
			if (M.getElem(j,i) > max)
			{
				max = M.getElem(j,i);
			}	
		}		
	}
	return max;
	//---------YOUR matrix_max CODE ENDS HERE (optional helper function)----------
}

int main(int argc, char *argv[]) {

	//Init
	MPI_Init (&argc, &argv);
	int rank (0), size (0);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	//Read from file
	Matrix M(0,0), result(0,0);
	if (rank == 0){
		std::string filename = argv[1];
		std::ifstream ifs(filename);
		M.read(ifs);
		M.getMajor() == "row-major" ? result.setDim(size,1) : result.setDim(1,size);
	}
	size_t n = M.getNcols();
	std::string major = M.getMajor();
	//Max Pooling
	//---------YOUR MAX POOLING CODE BEGINS HERE------------------
	// No std::cout can be used in the code you will upload
  	MPI_Bcast (&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  	const unsigned stripe = n / size;
	
  	Matrix local_A(major,stripe,n);

  	MPI_Scatter (
    M.data (), stripe * n, MPI_DOUBLE,
    local_A.data (), stripe * n, MPI_DOUBLE,
    0, MPI_COMM_WORLD);
	double local_max = matrix_max(local_A);

  	MPI_Gather(&local_max, 1, MPI_DOUBLE, result.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	//---------YOUR MAX POOLING CODE ENDS HERE---------------------

	//Output
	if(rank==0){
		// These are the only 2 std::cout allowed
		std::cout<<"Input matrix is:"<<std::endl;
		M.print()<<std::endl;
		std::cout<<"Max pooling gives: "<<std::endl;
		result.print();
	}

	//Finalize
	MPI_Finalize ();

	return 0;
}

