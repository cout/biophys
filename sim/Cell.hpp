#ifndef Cell__hpp
#define Cell__hpp

#include "Point.hpp"

class Cell
  : public Point
{
public:
  Cell();

  double radius;
  double sodium_permeability;
  double potassium_permeability;
};

#endif // Cell__hpp
