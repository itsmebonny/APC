#include<iostream>
#include<vector>
#include<openmpi/mpi.h>


bool is_prime (unsigned n);

std::vector<unsigned> get_prime_numbers (unsigned min, unsigned max){
    
}

int main (int argc, char *argv[])
{
    // init
    MPI_Init(&argc, &argv);
    // initialize rank and size
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // read parameters from command-line
    unsigned min = *argv[1];
    unsigned max = *argv[2];
    // get the vector of prime numbers
    std::vector<unsigned> prime_numbers = get_prime_numbers(min, max);
    // rank 0 prints the prime numbers
    if (rank == 0)
    {
        std::cout << "prime numbers between " << min << " and " << max
        << " are:" << std::endl;
        for (unsigned n : prime_numbers)
            std::cout << n << " ";
            std::cout << std::endl;
    }
    // finalize
    MPI_Finalize();
    return 0;
}