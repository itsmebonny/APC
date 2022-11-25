//
// Created by Danilo Ardagna on 2019-09-28.
//
#include "Book.h"
#include "Library.h"

void Library::addBook(const Book & book){
    books.push_back(book);
}
void Library::print() const{
        for(auto i:books)
            i.print();
}
int Library::findAvailableBook(const string & author, const string & title) const{
    size_t ret_index = -1; // if it doesn't find it
    bool book_found = false;
    for (size_t i = 0; i < books.size() && !book_found; i++)
    {
        if (books[i].equal_to(author, title))
        {
            book_found = true;
            ret_index = i;
        }
        
    }
    return ret_index;
}
int Library::findByCode(unsigned code) const{
    size_t ret_index = -1; // if it doesn't find it
    bool book_found = false;
    for (size_t i = 0; i < books.size() && !book_found; i++)
    {
        if (books[i].get_code() == code)
        {
            book_found = true;
            ret_index = i;
        }
        
    }
    return ret_index;
}
int Library::rentBook(const string & author, const string & title){
    int index = findAvailableBook(author, title);
    if (index == -1)
    {
        cout << "The book's not available or doesn't exists";
    }
    else
    {
        books[index].set_available(false);

    }
    return index;
}
bool Library::returnBook(unsigned code){
    int index = findByCode(code);
    if (index == -1)
    {
        cout << "The book doesn't exists \n";
        return false;
    }
    else
    {
      if (books[index].is_available())
        {
            cout << "The book is already available \n";
            return false;
        }
        else
        {
            books[index].set_available(true);
            cout << "Book returned \n";
            return true;
        }
        
    }
       
 }
void Library::printOldest() const{
    int oldest = 30000;
    int index = 0;
    for(auto i:books){
        if (i.get_year() < oldest){
            oldest = i.get_year();
            index = i.get_code();
        }
        }
    int oldest_book = findByCode(index);
    books[oldest_book].print();
}
void Library::printLongest() const{
    int longest = 0;
    int index = 0;
    for(auto i:books){
        if (i.get_pages() > longest){
            longest = i.get_pages();
            index = i.get_code();
        }
        }
    int longest_book = findByCode(index);
    books[longest_book].print();
}