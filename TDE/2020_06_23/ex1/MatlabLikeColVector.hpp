#ifndef MATLABLIKECOLVECTOR_HPP
#define MATLABLIKECOLVECTOR_HPP
#include "MatlabLike2DVector.hpp"
class MatlabLikeColVector:public MatlabLike2DVector
{
public:
    MatlabLikeColVector(size_t rows):MatlabLike2DVector(rows, 1){};
    double operator() (size_t i){
        return data[i][0];
    }
    double operator() (size_t i) const {
        return data.at(i).at(0);
    }
};

#endif //MATLABLIKECOLVECTOR_HPP