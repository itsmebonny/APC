#ifndef SALESDATA_H
#define SALESDATA_H

#include<iostream>
#include<vector>
#include<string>

class SalesData
{
private:
    std::string BookNo = "";
    unsigned units_sold = 0;
    double revenue = 0;
public:
    SalesData(void) = default;
    SalesData(const std::string &bn, unsigned u, double r): BookNo(bn), units_sold(u), revenue(r){};
    std::string isbn (void) const {return BookNo;}
    unsigned get_unists_sold(void) {return units_sold;}
    double get_revenue(void) {return revenue;}
    // combine
    SalesData& combine (const SalesData &);
    // average price
    double avg_price (void) const;
    // print
    void print (void) const;
};
#endif //SALESDATA_H