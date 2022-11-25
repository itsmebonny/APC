/*
 * Function.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include <cmath>

#include "Function.h"

double Function::eval (double x) const
{
    double val = 0.0;
    for (size_t i = 0; i < coefficients.size()-1; i++)
    {
        val += coefficients[i] * pow(x,i);
    }
    return val;
}

Function Function::derivative() const
{
    std::vector<double> dcoeffs;

    // f(x) = a_0 + a_1*x + a_2 * x^2...
    //f'(x) = a_1 + a_2 * x + ...

    for (size_t i = 0; i < coefficients.size(); i++)
    {
        dcoeffs.push_back((i+1) * coefficients[i+1]);
    }
    

    return Function(dcoeffs);
}

void Function::print() const
{
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        std::cout << coefficients[i] << " ";
    }
    std::cout << std::endl;
    
}