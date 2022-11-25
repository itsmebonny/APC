//
//  Matrix.cpp
//  Determinant2
//
//  Created by ing.conti on 07/10/22.
//

#include <vector>
#include <iostream>

#include "Matrix.h"


Matrix::Matrix( size_t nRows, size_t nCols) {
    for (size_t i = 0; i < nRows; i++)
    {   
        data.push_back(std::vector<double>(nCols, 0));  
    }
}


double Matrix::getElem(size_t i, size_t j) const{
    
    if(i < data.size() && j < data[i].size())
        return data[i][j];
    else
    	return INVALID; 

}

void Matrix::erase_row(size_t i){
    data.erase(data.begin() + i);
}

void Matrix::erase_col(size_t j){
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i].erase(data[i].begin() + j);
    }
}


double Matrix::cofactor(size_t i, size_t j) const{
    Matrix temp(data);
    temp.erase_col(j);
    temp.erase_row(i);
    if ((i + j) % 2 == 0)
        return temp.determinant();
    else
        return -temp.determinant();
    
}


double Matrix::determinant() const{
    // check if it's a square matrix
    
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].size() != data.size())
        {
            return INVALID;
        }
        
    }
    
    // use laplace to compute the determinant
    
    double det = 0;
    if (data.size() == 1)
    {
        return data[0][0];
    }
    
    else if (data.size() == 2) 
    {
        return data[0][0]*data[1][1] - data[0][1]*data[1][0];
    }
    else if (data.size() == 3) 
    {
        return data[0][0]*data[1][1]*data[2][2] + 
            data[0][1]*data[1][2]*data[2][0] + 
            data[0][2]*data[1][0]*data[2][1] - 
            data[2][0]*data[1][1]*data[0][2] - 
            data[2][1]*data[1][2]*data[0][0] - 
            data[2][2]*data[1][0]*data[0][1];
    }
    
    else
    {
        for (size_t i = 0; i < data.size(); i++)
        {   
            det += data[i][0]*cofactor(i,0);          
        }    
    } 
    return det;
    //return INVALID;
}

void Matrix::print() const{
    for(int i=0;i<data.size();i++){
    for(int j=0;j<data[i].size();j++){
        std::cout << data[i][j] << " ";
    }
    std::cout << std::endl;
}
}
