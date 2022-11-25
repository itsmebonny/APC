#include "Path.h"

Path::Path(unsigned int l) : length(l) {}

Path::Path(Path& p) : length(p.length) {
  avgRating = p.avgRating;
}

unsigned Path::getPoints() {
  return (avgRating * 2) / length;
}

void Path::rate(unsigned int rating) {
  if (rating < 1 || rating > 10)
  {
    std::cerr << "Rating not valid" << std::endl;
  }
  else
    avgRating = ((avgRating * numOfReviews) + rating)/(numOfReviews++);
};