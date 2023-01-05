#ifndef ND_VECTOR
#define ND_VECTOR
#include<iostream>
#include<vector>
#include<openmpi/mpi.h>
#include<cmath>

namespace numeric
{
class nd_vector
{
typedef std::vector<double> container_type;
container_type x;
public:
typedef container_type::value_type value_type;
typedef container_type::size_type size_type;
typedef container_type::pointer pointer;
typedef container_type::const_pointer const_pointer;
typedef container_type::reference reference;
typedef container_type::const_reference const_reference;
explicit nd_vector (size_type n = 0);
nd_vector (std::initializer_list<double>);
size_type size (void) const;
void read (std::ifstream & input_stream);

void print() const;
reference operator [] (size_type);
value_type operator [] (size_type) const;
pointer data (void);
const_pointer data (void) const;
};
}
#endif //ND_VECTOR
double cosine_similarity (const numeric::nd_vector & a, const numeric::nd_vector & b){
    int rank, size;
    double sum = 0, norm_a = 0, norm_b = 0;
    double total_sum = 0, total_norm_a = 0, total_norm_b = 0;
    for (size_t i = 0; i < a.size()/size; i++)
    {
        sum += a[i+rank*a.size()/size]*b[i+rank*a.size()/size];
        norm_a += a[i+rank*a.size()/size]*a[i+rank*a.size()/size];
        norm_b += b[i+rank*a.size()/size]*b[i+rank*a.size()/size];
    }
    MPI_Reduce(&sum, &total_sum, size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&norm_a, &total_norm_a, size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&norm_b, &total_norm_b, size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return total_sum/(std::sqrt(total_norm_a)*std::sqrt(total_norm_b));
}
