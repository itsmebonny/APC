#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include<string>

class Product
{
protected:
    std::string description;
public:
    Product(const std::string & description):description(description){};
    virtual float get_cost() const = 0;
};


#endif //PRODUCT_HPP