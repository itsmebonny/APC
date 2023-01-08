#ifndef CART_H
#define CART_H
#include<vector>
class Cart
{
private:
    float total;
    std::vector<unsigned> products;
public:
    Cart();
    void add_to_cart(unsigned product_id,
    float price);
    float get_total() const;
};

#endif //CART_H