#include "StringSkipList.hpp"
int main(){
    StringSkipList s1({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29" });
    s1.print();
    if (s1.find("14") != s1.end())
        std::cout << "found" << std::endl;
    else
        std::cout << "not found" << std::endl;    s1.insert("60");
    s1.insert("45");
    if (s1.find("60") != s1.end())
        std::cout << "found" << std::endl;
    else
        std::cout << "not found" << std::endl;
    s1.print();
    return 0; 
}