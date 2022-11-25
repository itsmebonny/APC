

#include "Path.h"

class HikingPath:public Path
{
private:
    unsigned height = 0;
public:
    HikingPath(unsigned l, unsigned h);

    void set_points();
    unsigned getPoints() override;
 
};


