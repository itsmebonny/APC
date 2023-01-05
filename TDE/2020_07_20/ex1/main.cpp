#include"Review.hpp"
#include"Book.hpp"
#include"GoodReads.hpp"

int main() {
    
    GoodReads g1;
    Book b1("gogoog", "dojdowjdwo", "dowdokd", 90);
    Book b2("gogdwaaaaaaaaaoog", "dojddwaadwdwadwaowjdwo", "ddawdawwdaowdokd", 90000000);
    Review r1("gogoog", "emozionante", 1);
    Review r2("gogoog", "adoro", 3);
    Review r3("gogoog", "emozionante", 5);
    Review r4("gogdwaaaaaaaaaoog", "adodwdwdwro", 2);
    Review r5("gogdwaaaaaaaaaoog", "emoziolmllknante", 4);
    Review r6("gogdwaaaaaaaaaoog", "adomlmlro", 3);
    g1.add_book("gogoog", "dojdowjdwo", "dowdokd", 90);
    g1.add_book("gogdwaaaaaaaaaoog", "dojddwaadwdwadwaowjdwo", "ddawdawwdaowdokd", 90000000);
    g1.add_review("gogoog", "emozionante", 1);
    g1.add_review("gogoog", "adoro", 3);
    g1.add_review("gogoog", "emozionante", 5);
    g1.add_review("gogdwaaaaaaaaaoog", "adodwdwdwro", 2);
    g1.add_review("gogdwaaaaaaaaaoog", "emoziolmllknante", 4);
    g1.add_review("gogdwaaaaaaaaaoog", "adomlmlro", 3);

    
    
    
    return 0;
}