#include "SalesArchive.hpp"

SalesArchive SalesArchive::reduce_by_book(void) const{
    std::vector<SalesData> new_archive;
    std::vector<SalesData> copy_archive = archive;

    for (size_t i = 0; i < copy_archive.size(); i++){
        new_archive.push_back(copy_archive[i]);
        copy_archive.erase(copy_archive.begin()+i);
        for (size_t j = 0; j < copy_archive.size(); j++)
        {   
            if (new_archive[i].isbn() == copy_archive[j].isbn())
            {   
                new_archive.at(i).combine(copy_archive[j]);
            }
            
        }
    }
    SalesArchive result(new_archive);
    return result;
}
void
SalesArchive::print_archive (void) const
{
    std::vector<SalesData>::const_iterator cit;
    for (cit=archive.cbegin(); cit!=archive.cend(); cit++)
        cit->print();
}