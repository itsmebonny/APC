#ifndef TRAVEL_HPP
#define TRAVEL_HPP
#include<string>
#include<memory>
#include "Product.hpp"
class Travel
{
private:
    std::string depart_date;
    std::string return_date;
    std::string destination;
    std::vector<std::shared_ptr<Product>> products;
    std::vector<size_t> customer_indeces;
public:
    Travel(const std::string & depart_date,
        const std::string & return_date,
        const std::string & destination):depart_date(depart_date), return_date(return_date), destination(destination){};
    void add_product(std::shared_ptr<Product> &p){
        products.push_back(p);
    }
    float compute_cost() const{
        float total = 0;
        for (auto i: products){
            total += i->get_cost();
        }
        return total;
    };
};

#endif //TRAVEL_HPP