 #include <openmpi/mpi.h>
 #include "DenseMatrix.hpp"
 #include<cmath>
 int main(int argc, char * argv[]){
    MPI_Init (&argc, &argv);
    int rank (0), size (0);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    std::string file_name = argv[1];  
    double norm = frobenius_norm(file_name);
    if (rank == 0)
    std::cout << norm << std::endl;
    MPI_Finalize ();
    return 0;
 }
 double frobenius_norm(std::string &file_name){
    std::ifstream f(file_name);
    la::dense_matrix matrix;
    matrix.read(f);
    int rank, size;
    size_t m = matrix.rows();
    size_t n = matrix.columns();
    MPI_Bcast(&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    size_t stripe = m/size;
    la::dense_matrix local(stripe, n);
    MPI_Scatter(&matrix.data(), stripe * n, MPI_DOUBLE, &local.data(), stripe*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    int sum = 0, total_sum = 0;
    for (size_t i = 0; i < stripe; i++)
    {
        for (size_t j = 0; i < n; j++)
        {
            sum += std::abs(local(i, j))*std::abs(local(i, j));
        }
        
    }
    MPI_Reduce(&sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return std::sqrt(total_sum);
 }