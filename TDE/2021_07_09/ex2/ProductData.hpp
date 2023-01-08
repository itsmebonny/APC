#ifndef PRODUCTDATA_H
#define PRODUCTDATA_H
#include<string>
#include<vector>
class ProductData
{
private:
    std::string description;
    float price = 0;
    std::vector<std::vector<unsigned>> similar_products;
public:
    ProductData(const std::string & description, float price,
const std::vector<unsigned> &similar_products_ids):description(description), price(price){
    similar_products.push_back(similar_products_ids);
};
    ProductData();
    void add_similar_product(unsigned product_id);
    float get_price() const;
    const std::string & get_description() const;
    const std::vector<unsigned> get_similar_products() const;
};

#endif //PRODUCTDATA_H