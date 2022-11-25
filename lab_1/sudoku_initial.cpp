/*
 * Check sudoku matrix
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;




/*
 * YOUR CODE GOES HERE
 */

int basic_search (const unsigned v[], unsigned n_elements);
int check_rows(const unsigned sudoku[][SIZE]);
int check_cols(const unsigned sudoku[][SIZE]);
int check_regions(const unsigned sudoku[][SIZE]);


// Return:
//         1 if sudoku matrix complies to all Sudoku rules
//        -1 if a row violates the game rules
//        -2 if a column violates the game rules
//        -3 if a region violates the game rules
int check_sudoku(const unsigned sudoku[][SIZE]);

// Create a Sudoku matrix by Lewis' Algorithm
// (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)
void generate_sudoku(unsigned sudoku[][SIZE]);

int main()
{
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

    // check
    int res = check_sudoku(sudoku);
    std::cout << "check_sudoku returns: " <<  res << endl;

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);

    // check
    res = check_sudoku(sudoku2);
    cout << "check_sudoku returns: " <<  res << endl;

    return 0;
}

int search_key (const unsigned v[], unsigned n_elements, unsigned key)
{
    unsigned key_found = 0;

    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            key_found = 1;

    return key_found;
}


int basic_search (const unsigned v[], unsigned n_elements){
    unsigned sequence[n_elements];
    unsigned sum = 0;
    for (unsigned i = 0; i < n_elements; i++)
    {
        sequence[i] = i+1;
    }
    
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
int check_rows(const unsigned sudoku[][SIZE]){
    unsigned v[SIZE];
    for (unsigned i = 0; i < SIZE; i++){
        for (unsigned j = 0; j < SIZE; i++)
        {
            v[j] = sudoku[i][j];
        }
        if (basic_search(v, SIZE) == 0){
            return 0;
        }
    }
    return 1;

    }
int check_cols(const unsigned sudoku[][SIZE]){
   unsigned v[SIZE];
    for (unsigned i = 0; i < SIZE; i++){
        for (unsigned j = 0; j < SIZE; i++)
        {
            v[j] = sudoku[j][i];
        }
        if (basic_search(v, SIZE) == 0){
            return 0;
        }
    }
    return 1;

}
int check_regions(const unsigned sudoku[][SIZE]){
    
    unsigned k = 0;
    unsigned t = 0;
    while (k < SIZE)
    {
        t = 0;
    while (t < SIZE)
    {
    unsigned v[SIZE];
    unsigned n = 0;
    for (unsigned i = 0; i < SIZE/3; i++)
    {
        for (unsigned j = 0; j < SIZE/3; i++)
        {
            v[n] = sudoku[i+t][j+k];
            n++;
        }
        
    }
    if(basic_search(v, SIZE) == 0){
        return 0;
    }
    t += 3;}
    k += 3;}
}


int check_sudoku(const unsigned sudoku[][SIZE])
{       
    unsigned result_rows = check_rows(sudoku);
    unsigned result_cols = check_cols(sudoku);
    unsigned result_regions = check_regions(sudoku);
    cout << "To be implemented" << endl;
    if (result_rows == 0)
    {
        return -1;
    }
    else if (result_cols == 0)
    {
        return -2;
    }
    else if (result_regions == 0)
    {
        return -3;
    }
    else
    {
        return 1;
    }
    
    
    
    return 0;
}

void generate_sudoku(unsigned sudoku[][SIZE])
{
    int x = 0;
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}