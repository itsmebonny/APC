#include "StepwiseInterpolation.h"

/* TO BE COMPLETED */

StepwiseInterpolation::StepwiseInterpolation (const std::vector<Point> & points):Interpolation(points){}

double
StepwiseInterpolation::interpolate (double x) const
{
   if (x < points[0].get_x() || x > points[points.size()-1].get_x())
        return INVALID;
    for (std::size_t i = 1; i < points.size(); i++){
        if (x >= points.at(i-1).get_x() && x <= points.at(i).get_x()){
            return points[i-1].get_y();
        }
    }
}
