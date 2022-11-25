#include "Centroid.h"

void
Centroid::update_coords (std::vector<Point *> const & ps)
{
    std::vector<double> new_coords(x.size(), 0);
    for (size_t i = 0; i < ps.size(); i++)
    {
        for (size_t j = 0; j < new_coords.size(); j++)
        {
            new_coords[j] += ps[i]->get_coord(j);
        }
        
    }
    
}
