#ifndef BOOK_H
#define BOOK_H

#include<string>

class Book
{
private:
    std::string title;
    std::string author;
    std::string publisher;
    unsigned pages;
public:
    Book(std::string t, std::string a, std::string pub, unsigned p): title(t), author(a), publisher(pub), pages(p){};
};

#endif //BOOK_H