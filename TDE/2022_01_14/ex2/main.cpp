#include<openmpi/mpi.h>
#include<string>

#ifndef DENSE_MATRIX_HH
#define DENSE_MATRIX_HH
#include <fstream>
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

la::dense_matrix cumsum_col (const la::dense_matrix& local_M){
    la::dense_matrix res_local(local_M.rows(), local_M.columns()), res(local_M.rows()*size, local_M.columns());

    for (size_t i = 0; i < local_M.rows(); i++)
    {   
        res_local(i, 0) = local_M(i, 0);
        for (size_t j = 1; j < local_M.columns(); j++)
        {
            res_local(i,j) = res(i, j-1) + local_M(i,j);
        }
        
    }
    MPI_Gather(&res_local.data(), res_local.rows()*res_local.columns(), MPI_DOUBLE, &res.data(), res_local.rows()*res_local.columns(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
    return res;
}

int main (int argc, char *argv[])
{
// MPI initialization
MPI_Init(&argc, &argv);
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
std::string filename;
std::cin >> filename;
la::dense_matrix M;
if (rank == 0){
    std::ifstream f(filename);
    M.read(f);
}
size_t rows = M.rows(), cols = M.columns();
MPI_Bcast(&rows, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
MPI_Bcast(&cols, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
size_t locs = rows/size;
la::dense_matrix local_M(locs, cols);
MPI_Scatter(&M.data(), locs*cols, MPI_DOUBLE, &local_M.data(), locs*cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
// compute cumulative sum by column
la::dense_matrix S = cumsum_col(local_M);
if (rank == 0)
{
std::cout << "Matrix after cumsum: " << std::endl;
S.print(std::cout);
}
MPI_Finalize();
return 0;
}