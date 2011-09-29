#ifndef Particle__hpp
#define Particle__hpp

#include "Point.hpp"

class System;

class Particle
  : public Point
{
public:
  Particle()
    : Point(0, 0, 0)
  {
  }

  void random_walk(
      System const & system,
      double max_movement,
      double cell_permeability);
};

#endif // Particle__hpp
