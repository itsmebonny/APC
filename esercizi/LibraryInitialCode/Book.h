//
// Created by Danilo Ardagna on 2019-09-28.
//

#ifndef LIBRARYINITIALCODE_BOOK_H
#define LIBRARYINITIALCODE_BOOK_H


#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Book {
private:
    unsigned code;
    unsigned year;
    unsigned pages;
    string author;
    string title;
    bool available;

public:
    Book(unsigned c, unsigned y, unsigned p,
    const string &a, const string &t, bool av):
    code(c),
    year(y),
    pages(p),
    author(a),
    title(t),
    available(av){};

    unsigned get_code() const;
    unsigned get_year() const;
    unsigned get_pages() const;
    string get_author() const;
    string get_title() const;
    bool is_available() const;

    void set_available(bool av);

    void print() const;

    bool equal_to(const string &aut, const string &t) const;

};


#endif //LIBRARYINITIALCODE_BOOK_H
