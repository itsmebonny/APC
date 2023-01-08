
#include<openmpi/mpi.h>
#include<vector>

#ifndef DENSE_MATRIX_HH
#define DENSE_MATRIX_HH
#include <istream>
#include <vector>
namespace la // Linear Algebra
{
class dense_matrix final
{
typedef std::vector<double> container_type;
public:
typedef container_type::value_type value_type;
typedef container_type::size_type size_type;
typedef container_type::pointer pointer;
typedef container_type::const_pointer const_pointer;
typedef container_type::reference reference;
typedef container_type::const_reference const_reference;
private:
size_type m_rows, m_columns;
container_type m_data;
size_type
sub2ind (size_type i, size_type j) const;
public:
dense_matrix (void) = default;
dense_matrix (size_type rows, size_type columns,
const_reference value = 0.0);
explicit dense_matrix (std::istream &);
void
read (std::istream &);
void
swap (dense_matrix &);
reference
operator () (size_type i, size_type j);
const_reference
operator () (size_type i, size_type j) const;
size_type
rows (void) const;
size_type
columns (void) const;
dense_matrix
transposed (void) const;
pointer
data (void);
const_pointer
data (void) const;
void
print (std::ostream& os) const;
};
dense_matrix
operator * (dense_matrix const &, dense_matrix const &);
void
swap (dense_matrix &, dense_matrix &);
}
#endif // DENSE_MATRIX_HH

void print_matrix (const std::vector<la::dense_matrix>& C);
la::dense_matrix init_matrices(std::vector<la::dense_matrix> A, std::vector<la::dense_matrix> B);
int main (int argc, char *argv[])
{
MPI_Init(&argc, &argv);
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
std::vector<la::dense_matrix> A;
std::vector<la::dense_matrix> B;
std::vector<la::dense_matrix> C(A.size());
size_t size_A = A.size();
MPI_Bcast(&size_A, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
if (rank == 0)
init_matrices(A, B);

for (size_t i = rank; i < size; i++)
{
    la::dense_matrix local_A;
    la::dense_matrix local_B;
    for (size_t j = 0; j < size_A/size; j++)
    {
        size_t n = A[j+rank*size].rows();
        MPI_Send(&n, 1, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&A[j+rank*size].data(), n*n, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        MPI_Send(&B[j+rank*size].data(), n*n, MPI_DOUBLE, i, 2, MPI_COMM_WORLD);
        MPI_Recv(&local_A.data(), n*n, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&local_B.data(), n*n, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        la::dense_matrix local_C = local_A*local_B;
        MPI_Send(&local_C.data(), n*n, MPI_DOUBLE, i, 3, MPI_COMM_WORLD);
        MPI_Recv(&C[j+rank*size].data(), n*n, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
}

/*
YOUR CODE GOES HERE
*/
MPI_Finalize();
return 0;
}