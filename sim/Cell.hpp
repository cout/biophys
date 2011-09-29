#ifndef Cell__hpp
#define Cell__hpp

#include "Point.hpp"

class Cell
  : public Point
{
public:
  Cell();

  double radius;

  double sodium_permeability;    // measured as a probability
  double potassium_permeability; // measured as a probability
};

#endif // Cell__hpp
