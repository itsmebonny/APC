#include <iostream>
#include <fstream>
//#include <mpi.h>
#include "item.hpp"
#include "multi_dim_knapsack.hpp"
using random_greedy::item;
using random_greedy::multi_dim_knapsack;
multi_dim_knapsack::solution_type random_greedy_search(const multi_dim_knapsack m,
unsigned local_iterations);
int main(int argc, char* argv[]) {
    MPI_Init();
    int rank, size;
    MPI_Comm_Rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_Size(MPI_COMM_WORLD, &size);
    if (argc != 3){}
        std::cerr << "Incorrect arguments" << std::endl;
        MPI_Finalize();
        return -1;
    }   
    int global_iterations = std::stoi(argv[1]);
    std::string filename = argv[2];
    // Define, as an example, a custom problem with size and weight equal to 100.
    // Items are built in the same way and they are available across all processes
    item i1(1,1,1);
    item i2(2,2,2);
    item i3(3,3,3);
    // MKP istance is built in the same way and it is available across all processes
    multi_dim_knapsack m(100,100,42);
    m.add_item(i1);
    m.add_item(i2);
    m.add_item(i3);
    
    multi_dim_knapsack::solution_type local_best_solution = random_greedy_search(m,
    global_iterations/size);
/* Your code goes here */
}