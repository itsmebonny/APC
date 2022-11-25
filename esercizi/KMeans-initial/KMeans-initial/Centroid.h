#ifndef CENTROID_H_
#define CENTROID_H_

#include <iostream>
#include <vector>

#include "Point.h"

class Centroid : public Point
{
public:
  Centroid (std::vector<double> const & coords)
    : Point (coords) {};
  
  void
  update_coords (std::vector<Point *> const & ps);
};

#endif /* CENTROID_H_ */
