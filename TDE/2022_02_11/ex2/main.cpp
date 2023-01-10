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
la::dense_matrix
circshift (const la::dense_matrix& M, const std::function<double(double)>& f, unsigned r){
    la::dense_matrix res = M, res_local(M.rows()/size, M.columns());
    for (size_t i = rank; i < M.rows(); i+=size)
    {
        for (size_t j = 0; j < M.columns(); j++)
        {
            if (i < r)
                size_t k = M.rows() - r + i;
            else
                size_t k = i - r;
            res_local(i,j) = f(M(k,j)); 
        }
    }
    MPI_Allgather(&res_local.data(), M.rows()/size * M.columns(), MPI_DOUBLE, &res.data(), M.rows()/size * M.columns(), MPI_DOUBLE, MPI_COMM_WORLD);
}