#include "NearestNeighborInterpolation.h"


NearestNeighborInterpolation::NearestNeighborInterpolation (const std::vector<Point> & points):Interpolation(points){}

double
NearestNeighborInterpolation::interpolate (double x) const
{   
    if (x < points[0].get_x() || x > points[points.size()-1].get_x())
        return INVALID;
    for (std::size_t i = 1; i < points.size(); i++){
        if (x >= points.at(i-1).get_x() && x <= points.at(i).get_x()){
            double distance = std::abs(points[i-1].get_x() - points[i].get_x());
            if (distance/2 <= std::abs(x-points[i].get_x()))
                return points[i-1].get_y();
            else
                return points[i].get_y();
            
        }
    }
}
