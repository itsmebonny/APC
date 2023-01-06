#ifndef TRANSFER_HPP
#define TRANSFER_HPP
#include "Product.hpp"
class Transfer : public Product
{
protected:
    float cost;
public:
    Transfer(const std::string & description, float cost):Product(description), cost(cost){};
};




#endif //TRANSFER_HPP