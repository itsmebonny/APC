#include "Path.h"
#include "HikingPath.h"



HikingPath(unsigned l, unsigned h): Path(l), height(h){};
unsigned HikingPath::getPoints(){
    return 10*length + height/100;
}
void HikingPath::rate(unsigned int rating) {
if (rating > 15)
    {
    std::cerr << "Rating not valid" << std::endl;
    }
    else
    avgRating = ((avgRating * numOfReviews) + rating)/(numOfReviews++);
}




