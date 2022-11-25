#include <iostream>

class Path {
protected:
    const unsigned length;
    unsigned avgRating = 5;
    unsigned numOfReviews = 0;
public:

    Path(unsigned l);

    Path(Path& p);

    unsigned getPoints();

    virtual void rate(unsigned rating);

    virtual ~Path() {};
};