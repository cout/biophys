#ifndef Cell__hpp
#define Cell__hpp

#include "Point.hpp"
#include "Ion_Characteristics.hpp"

class Cell
  : public Point
{
public:
  Cell();

  double radius;

  Ion_Characteristics sodium_characteristics;
  Ion_Characteristics potassium_characteristics;

  double sodium_permeability;    // measured as a probability
  double potassium_permeability; // measured as a probability
};

#endif // Cell__hpp
