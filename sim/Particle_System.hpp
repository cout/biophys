#ifndef Particle_System__hpp_
#define Particle_System__hpp_

#include "Particle.hpp"

#include <vector>

class Particle_System
{
public:
  Particle_System(size_t n);
  void random_walk(double max);

  typedef std::vector<Particle> Particles;
  Particles const & particles() { return particles_; }

private:
  Particles particles_;
};

#endif // Particle_System__hpp_

