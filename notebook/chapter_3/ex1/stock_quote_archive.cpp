#include "stock_quote_archive.hpp"

void stock_quote_archive::add_stock_quote(stock_quote stock){
    archive.push_back(stock);
}

void stock_quote_archive::add_last_sale_price(std::string tick, double price){
    for(auto i:archive){
        if (i.get_name() == tick)
            i.add_price(price);
    }
}
