#include <iostream>
#include <vector>
#include "Book.h"
#include "Library.h"


int main() {
    Book b1(1, 2013, 1399, "S. B. Lippman", "C++ primer", true);

    Book b2(2, 2013, 1361, "B. Stroustrup", "The C++ programming language", true);

    Book b3(3, 2018, 386, "F. Chollet", "Deep Learning with Python", true);

    Book b4(4, 2010, 1904, "A. C. Picchia", "La borraccia nel deserto", true);

    Book b5(5, 2002, 653, "O. Fono", "Tre allegri ragazzi morivano", true);

    Book b6(6, 2020, 342, "S. Cemo", "Torna a casa lessa", true);

    b1.print();
    b2.print();
    

    Library lib;

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);
    lib.addBook(b4);
    lib.addBook(b5);
    lib.addBook(b6);

    cout << "Start renting process \n" << endl;

    lib.rentBook("S. B. Lippman", "C++ primer");
    cout <<"\n" << endl;
    lib.print();
    
    cout << "Primer should not be available \n"<< endl;
    
    lib.returnBook(1);
    cout <<"\n" << endl;
    lib.print();

    cout << "Primer should be available \n"<< endl;

    lib.returnBook(1);
    cout <<"\n" << endl;
    lib.print();

    cout << "****************\n"<< endl;
    
    cout << "Oldest book" << endl;

    lib.printOldest();
    cout <<"*****************\n" << endl
    << "Longest book" << endl;
    lib.printLongest();
    return 0;

}