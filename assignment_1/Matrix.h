//
//  Matrix.h
//  Determinant2
//
//  Created by ing.conti on 07/10/22.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>

#include <limits>

constexpr double INVALID{ std::numeric_limits<double>::quiet_NaN() };


// DO NOT ALTER Class name.
class Matrix{

private:
    std::vector<std::vector<double>> data;

public:
    Matrix( size_t nRows, size_t nCols); // zeros matrix, only to allow run
    double getElem(size_t i, size_t j) const;
    double determinant() const; 
    // “YOUR CODE HERE”
    void print() const;
    double cofactor(size_t i, size_t j) const;
    void erase_row(size_t i);
    void erase_col(size_t i);
    Matrix(std::vector<std::vector<double>> d):data(d){};
    // Matrix m1 = Matrix( {{1, 2}, {3,4}}  );

};


#endif //MATRIX_H
