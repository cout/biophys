#ifndef Cell__hpp
#define Cell__hpp

#include "Point.hpp"

class Cell
  : public Point
{
public:
  Cell();

  double radius;
};

#endif // Cell__hpp
