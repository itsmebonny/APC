//
// Created by Danilo Ardagna on 2019-09-28.
//

#ifndef LIBRARYINITIALCODE_LIBRARY_H
#define LIBRARYINITIALCODE_LIBRARY_H
#include <vector>
#include <iostream>

#include "Book.h"


using std::vector;
using std::string;
using std::cerr;
using std::endl;

class Library {

private:
    vector<Book> books;

    // return the index of the book
    int find(const string & author, const string & title) const;

    int findByCode(unsigned code) const;

    // return the index of the first available book
    int findAvailableBook(const string & author, const string & title) const;

public:
    // add a book to the library
    void addBook(const Book & book);

    // return the book code or -1 if the book is not available
    int rentBook(const string & author, const string & title);

    // return to the library the book with the specified code.
    // Return false if the code is not found/the book is available
    // return true otherwise
    bool returnBook(unsigned code);

    void print() const;

    void printOldest() const;

    void printLongest() const;


};


#endif //LIBRARYINITIALCODE_LIBRARY_H
