#ifndef STOCK_QUOTE_H
#define STOCK_QUOTE_H
#include <iostream>
#include <vector>
class stock_quote
{
private:
    std::string ticker;
    std::vector<double> price;
public:
    stock_quote(void) = default;
    stock_quote(std::string t, std::vector<double> p):ticker(t), price(p){};
    void add_price(double p){price.push_back(p);}
    std::string get_name(){return ticker;}
    ~stock_quote();
};


#endif //STOCK_QUOTE_H
