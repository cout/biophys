#include "Particle_System.hpp"

Particle_System::
Particle_System(size_t n)
  : particles_(n)
{
}

void
Particle_System::
random_walk(double max)
{
  Particles::iterator it(particles_.begin());
  Particles::iterator end(particles_.end());

  for(; it != end; ++it)
  {
    it->random_walk(max);
  }

}

