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

bool check_probability_matrix (const la::dense_matrix& P){
    int rank, size;
    
    bool check_p = true, check_r = true, check_loc = false, check = false;
    for (size_t i = rank; i < P.columns() && check_r; i+=size)
    {
        size_t o = 0;
        double sum = 0;
        for (size_t j = 0; i < P.columns() && check_p; j++)
        {
            if(P(i,j) <=1 && P(i,j) >= 0)
                {sum += P(i,j);
                o++;}
            else
                check_p = false;
        }
        if (sum == 1 && o != P.columns())
            check_r = false;
        
    }
    if (check_r && check_p)
        check_loc = true;
    MPI_Reduce(&check_loc, &check, 1, MPI_CXX_BOOL, MPI_BAND, 0, MPI_COMM_WORLD);
    return check;    
}
std::vector<double> compute_probabilities (const la::dense_matrix& P,
const std::vector<std::vector<unsigned>>& trajectories){
        int rank, size;
        size_t n = trajectories.size();
        MPI_Bcast(&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
        size_t n_loc = n/size;
        if(rank == 0)
        {
            for (size_t i = 0; i < size; i++)
            {
                int dest = i % n_loc;
                for (size_t j = 0; j < n_loc; j++)
                {
                    size_t size_loc = trajectories[j].size();
                    MPI_Send(&size_loc, 1, MPI_UNSIGNED, dest, 0, MPI_COMM_WORLD);
                    MPI_Send(&trajectories[j][0], size_loc, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
                }
            }
    }
    std::vector<std::vector<unsigned>> trajectories_local(n_loc);
    std::vector<double> prob_local(n_loc), prob_total(n);
    for (size_t j = 0; j < n_loc; j++)
    {
        size_t size_loc;
        MPI_Recv(&size_loc, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&trajectories_local[j][0], size_loc, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    for (size_t i = 0; i < trajectories_local.size(); i++)
    {
        double prob = 0;
        for (size_t j = 1; i < trajectories_local[i].size(); i++)
        {
            prob *= P(trajectories_local[i][j-1], trajectories_local[i][j]);
        }
        prob_local[i] = prob;
    }
    MPI_Gather(&prob_local[0], n_loc, MPI_DOUBLE, &prob_total[0], n_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    return prob_total;
}