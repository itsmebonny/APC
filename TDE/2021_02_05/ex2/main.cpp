#include<openmpi/mpi.h>
#include<string>

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

typedef std::function<double(const la::dense_matrix&)> function_t;
la::dense_matrix evaluate_by_column(const la::dense_matrix& A, const function_t& f){
    int rank, size;
    size_t m = A.rows();
    size_t n = A.columns();
    size_t block = n/size;
    la::dense_matrix res(1, n);
    la::dense_matrix res_loc(1, block);
    MPI_Bcast(&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    for (i = 0; i < block; i++){
        la::dense_matrix col(m,1);
        for (size_t j = 0; j < m; j++)
        {
            col(j,0) =  A(j, rank*block+i);
        }
        res_loc(0, i) = f(col);
    }
    MPI_Gather(&res_loc.data(), block, MPI_DOUBLE, &res.data(), block, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    return res;


}