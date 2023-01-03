#ifndef MATLABLIKE2DVECTOR_HPP
#define MATLABLIKE2DVECTOR_HPP
#include <iostream>
#include <vector>
class MatlabLike2DVector
{
protected:
    std::vector<std::vector<double>> data;
public:
    MatlabLike2DVector(size_t rows, size_t cols){
        data.resize(rows, std::vector<double>(cols, 0.0));
    };
    double operator() (size_t r, size_t c){
        data.resize(r, std::vector<double>(c));
        return data[r][c];
    }
    double operator() (size_t r, size_t c) const {
        return data.at(r).at(c);
    }
    MatlabLike2DVector operator* (double scalar){
        MatlabLike2DVector result(this->data.size(), this->data.at(0).size());
        for (size_t i = 0; i < this->data.size(); i++)
        {
            for (size_t j = 0; j < this->data[0].size(); j++)
            {
                result.data[i][j] = scalar * this->data.at(i).at(j);
            }            
        }
        return result;
    }
    MatlabLike2DVector operator* (MatlabLike2DVector rhs){
        MatlabLike2DVector res(this->data.size(), rhs.data[0].size());
        double rows, cols;
        for (size_t i = 0; i < this->data.size(); i++)
        {
            for (size_t j = 0; j < rhs.data[0].size(); j++)
            {
                for (size_t k = 0; k < this->data.size(); k++)
                {
                    cols += rhs.data[i][k];
                }
                for (size_t m = 0; m < rhs.data[0].size(); m++)
                {
                    rows += this->data[m][j];
                }
                res.data[i][j] = rows + cols;
                rows = 0;
                cols = 0;
            }
        }
        return res;
    }
};

#endif //MATLABLIKE2DVECTOR_HPP