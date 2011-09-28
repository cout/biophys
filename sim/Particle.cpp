#include "Particle.hpp"

#include <cstdlib>

void
Particle::
random_walk(double max)
{
  x += (((2 * (double)std::rand()) / RAND_MAX) - 1.0) * max;
  y += (((2 * (double)std::rand()) / RAND_MAX) - 1.0) * max;
  z += (((2 * (double)std::rand()) / RAND_MAX) - 1.0) * max;
}

