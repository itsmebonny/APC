#include<openmpi/mpi.h>
#include<string>
#include<fstream>
#include<algorithm>
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
double fcrown_property (const std::string& filename){
    int rank,size;
    std::ifstream f(filename);
    la::dense_matrix A;
    A.read(f);
    size_t n = A.columns();
    MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    std::vector<double> crown_loc(4*n/size);
    std::vector<double> trace_loc(n/size);
    double trace, crown;
    if(rank == 0){
    for(size_t i = 0; i<n;i++){
        int dest = i/n;
        for(size_t j = 0; j<n; j++){
            if(i == j)
                MPI_Send(&A(i,j), 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
            else if((i == 0 && j == 0) || (i == n-1 && j == 0) || (i == 0 && j == n-1) || (i == n-1 && j == n-1))
                MPI_Send(&A(i,j), 1, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            }
        }
    }
    if(rank != 0){
        for(size_t i = 0; i < n/size; i++){
            MPI_Recv(&trace_loc[i], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for(size_t i = 0; i < 4*n/size; i++){
            MPI_Recv(&crown_loc[i], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    double t_total = 0, c_total = 0;
    for(auto i:trace_loc)
        t_total += i;
    for (auto i : crown_loc)
        c_total +=  i;
    MPI_Reduce(&t_total, &trace, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&c_total, &crown, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    return trace*crown;
}