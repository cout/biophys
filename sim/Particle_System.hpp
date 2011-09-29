#ifndef Particle_System__hpp_
#define Particle_System__hpp_

#include "Particle.hpp"

#include <vector>

class Particle_System
{
public:
  Particle_System(size_t n);

  void random_walk(
      System const & system,
      double max_movement,
      double cell_permeability);

  typedef std::vector<Particle> Particles;

  Particles const & particles() const { return particles_; }
  Particles & particles() { return particles_; }

  void draw();

private:
  Particles particles_;
};

#endif // Particle_System__hpp_

