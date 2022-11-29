#ifndef LINEAR_INTERPOLATION_HH
#define LINEAR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

/* TO BE COMPLETED */

class LinearInterpolation:public Interpolation
{

public:
  LinearInterpolation() = default;
  explicit LinearInterpolation (const std::vector<Point> &);

  double interpolate (double x) const override;
};

#endif // LINEAR_INTERPOLATION_HH
