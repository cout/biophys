#ifndef Sphere__hpp
#define Sphere__hpp

#include "Point.hpp"
#include <cmath>

class Sphere
  : public Point
{
public:
  Sphere()
    : radius(0)
  {
  }

  double radius;

  double surface_area() const
  {
    return 4 * M_PI * radius * radius;
  }
};

#endif // Sphere__hpp
