#ifndef SALESARCHIVE_H
#define SALESARCHIVE_H


#include"SalesData.hpp"

class SalesArchive{
private:
    std::vector<SalesData> archive;
public:
    SalesArchive(void) = default;
    SalesArchive(std::vector<SalesData> a):archive(a){};
    SalesArchive reduce_by_book(void) const;
    void print_archive (void) const;
};
#endif //SALESARCHIVE_H

