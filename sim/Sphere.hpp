#ifndef Sphere__hpp
#define Sphere__hpp

#include "Point.hpp"

class Sphere
  : public Point
{
public:
  Sphere()
    : radius(0)
  {
  }

  double radius;
};

#endif // Sphere__hpp
