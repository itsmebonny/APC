#include "SalesArchive.hpp"
#include "SalesData.hpp"

int main(){
    SalesData s1("Ciao", 10, 21.0);
    SalesData s2("Ciao", 103, 231.0);
    SalesData s3("Chela", 102, 2231.0);
    SalesData s4("Chela", 103, 2321.0);
    SalesData s5("Gatto", 104, 241.0);
    SalesData s6("Gatto", 1450, 2321.0);
    SalesData s7("Ciaop", 140, 221.0);
    std::vector<SalesData> v = {s1, s2, s3, s4, s5, s6, s7};
    SalesArchive archive(v);
    SalesArchive new_sa;
    std::cout << "==============" << std::endl;
    archive.print_archive();
    std::cout << "==============" << std::endl;
    std::cout << "Riduco" << std::endl;
    new_sa = archive.reduce_by_book();
    std::cout << "==============" << std::endl;
    new_sa.print_archive();
}