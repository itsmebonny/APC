#include "power_method.hpp"

DenseMatrix power_method(const DenseMatrix & local_A, std::size_t iterations)
{

  int cols = local_A.get_n_cols();
  int rows = local_A.get_n_rows();

  int rank (0), size (0);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  DenseMatrix x_new(cols, 1, 1);
  x_new = local_A*x_new;

  DenseMatrix res(rows*size, 1, 1);
  MPI_Allgather(x_new.data(), rows, MPI_DOUBLE, res.data(), rows, MPI_DOUBLE, MPI_COMM_WORLD);
for(size_t i = 1; i < iterations; i++){
  DenseMatrix res_new = local_A*res;
  MPI_Allgather(res_new.data(), rows, MPI_DOUBLE, res.data(), rows, MPI_DOUBLE, MPI_COMM_WORLD);
  if(rank==0){
    std::cout << "==========================" << std::endl;
    print(res);
    std::cout << "==========================" << std::endl;
  }
}
  return res;
  
}
