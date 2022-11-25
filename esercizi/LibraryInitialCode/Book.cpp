//
// Created by Danilo Ardagna on 2019-09-28.
//

#include "Book.h"

using std::cout;

unsigned Book::get_code() const{
    return code;
}
unsigned Book::get_year() const{
    return year;
}
unsigned Book::get_pages() const{
    return pages;
}
string Book::get_author() const{
    return author;
}
string Book::get_title() const{
    return title;
}
bool Book::is_available() const{
    return available;
}

void Book::set_available(bool av){
    available = av;
}

void Book::print() const{
    cout << code << endl
    << year << endl
    << pages<< endl
    << author << endl
    << title << endl;
    if(available)
    cout << "is available \n" << endl;
    else
        cout << "not available \n" << endl;

}

bool Book::equal_to(const string &aut, const string &t) const{

    return author == aut && title == t;
}