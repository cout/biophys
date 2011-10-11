#ifndef Cell__hpp
#define Cell__hpp

#include "Point.hpp"
#include "Ion.hpp"

class Cell
  : public Point
{
public:
  Cell();

  double radius;

  double permeability(Sodium_Ion const &) const { return 0.4; }
  double permeability(Potassium_Ion const &) const { return 0.4; }
};

#endif // Cell__hpp
