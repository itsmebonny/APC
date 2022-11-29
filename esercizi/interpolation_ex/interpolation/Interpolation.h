#ifndef INTERPOLATION_HH
#define INTERPOLATION_HH

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>

constexpr double INVALID{ std::numeric_limits<double>::quiet_NaN() };

#include "Point.h"

class Interpolation
{
   /* TO BE COMPLETED */
protected:
  std::vector<Point> points; // sorted_vector

public:
  Interpolation() = default;
  Interpolation(std::vector<Point> p);
  virtual double interpolate (double x) const = 0; 
};

#endif // INTERPOLATION_HH
