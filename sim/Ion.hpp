#ifndef Ion__hpp
#define Ion__hpp

#include "Point.hpp"

class System;
class Ion_Characteristics;

class Ion
  : public Point
{
public:
  Ion()
    : Point(0, 0, 0)
  {
  }

  void random_walk(
      System const & system,
      double max_movement,
      Ion_Characteristics & ion_characteristics);
};

#endif // Ion__hpp
