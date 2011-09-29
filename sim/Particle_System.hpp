#ifndef Particle_System__hpp_
#define Particle_System__hpp_

#include "Particle.hpp"

#include <vector>

class Particle_System
{
public:
  Particle_System(size_t n, double charge);

  void random_walk(
      System const & system,
      double max_movement,
      double cell_permeability);

  typedef std::vector<Particle> Particles;

  Particles const & particles() const { return particles_; }
  Particles & particles() { return particles_; }

  void draw();

  void charge_inout_sphere(Point sc, double r, double * in, double * out) const;

private:
  double n_;
  double charge_;
  Particles particles_;
};

#endif // Particle_System__hpp_

