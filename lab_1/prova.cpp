#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;


int basic_search (const unsigned v[], unsigned n_elements);
int main()
{   unsigned esito = 4;
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    };
    unsigned int prova[] = {1, 2, 3, 9, 5, 6, 7, 8, 9};
    esito = basic_search(prova, 9);
    std::cout << esito << std::endl;
    return 0;
    
}
int basic_search (const unsigned v[], unsigned n_elements){
    unsigned sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned sum = 0;
    for (unsigned i=0; i<n_elements; ++i){
        for (unsigned j = 0; j < n_elements; j++)
        {
            if (v[i] == 0 || v[i] > 9)
            {
                return 0;
            }
            else if (v[i] == sequence[j])
            {
                sequence[j] = 0;
            }
        }
        
    }
    for (unsigned i = 0; i < n_elements; i++)
    {
        sum += sequence[i];
        
    }
    if (sum == 0)
    {
        return 1;
    }
    else{
        return 0;
    }
    
    
}