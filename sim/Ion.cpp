#include "Ion.hpp"
#include "System.hpp"
#include "util.hpp"

#include <cstdlib>

void
Ion::
random_walk(
    System const & system,
    double max_movement,
    double cell_permeability)
{
  Point p = random_insphere(0, max_movement);
  p.x += x;
  p.y += y;
  p.z += z;

  if (system.valid_walk(*this, p, cell_permeability))
  {
    x = p.x;
    y = p.y;
    z = p.z;
  }
}

