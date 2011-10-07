#include "Ion.hpp"
#include "System.hpp"
#include "util.hpp"

#include <cstdlib>

void
Ion::
random_walk(
    System const & system,
    double max_movement,
    Ion_Characteristics & ion_characteristics)
{
  Point p = random_insphere(0, max_movement);
  p.x += x;
  p.y += y;
  p.z += z;

  system.try_walk(*this, p, ion_characteristics);
}

