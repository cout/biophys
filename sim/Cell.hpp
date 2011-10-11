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
  double sodium_inside;
  double sodium_outside;
  double potassium_inside;
  double potassium_outside;

  double permeability(Sodium_Ion const &) const { return 0.4; }
  double permeability(Potassium_Ion const &) const { return 0.4; }

  void move_inside(Sodium_Ion const &)
  {
    --sodium_outside;
    ++sodium_inside;
  }

  void move_outside(Sodium_Ion const &)
  {
    --sodium_inside;
    ++sodium_outside;
  }

  void move_inside(Potassium_Ion const &)
  {
    --potassium_outside;
    ++potassium_inside;
  }

  void move_outside(Potassium_Ion const &)
  {
    --potassium_inside;
    ++potassium_outside;
  }
};

#endif // Cell__hpp
