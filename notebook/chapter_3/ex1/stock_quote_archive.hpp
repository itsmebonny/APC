#ifndef STOCK_QUOTE_ARCHIVE_H
#define STOCK_QUOTE_ARCHIVE_H

#include <iostream>
#include <vector>
#include "stock_quote.hpp"

class stock_quote_archive
{
private:
    std::vector<stock_quote> archive;
public:
    stock_quote_archive(void) = default;
    stock_quote_archive(std::vector<stock_quote> a):archive(a){};
    ~stock_quote_archive();

    void add_stock_quote(stock_quote stock);
    void add_last_sale_price(std::string tick, double price);
};

#endif //STOCK_QUOTE_ARCHIVE_H
