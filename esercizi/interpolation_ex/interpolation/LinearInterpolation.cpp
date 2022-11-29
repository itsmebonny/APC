#include "LinearInterpolation.h"


LinearInterpolation::LinearInterpolation (const std::vector<Point> & points):Interpolation(points){}

double
LinearInterpolation::interpolate (double x) const
{
    if (x < points[0].get_x() || x > points[points.size()-1].get_x())
        return INVALID;
    for (std::size_t i = 1; i < points.size(); i++){
        if (x >= points.at(i-1).get_x() && x <= points.at(i).get_x())
            return ((points.at(i-1).get_y() - points.at(i).get_y())/(points.at(i-1).get_x() - points.at(i).get_x()))*(x - points.at(i).get_x()) + points.at(i).get_y();
    }

    
}
