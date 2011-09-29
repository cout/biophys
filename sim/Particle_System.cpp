#include "Particle_System.hpp"
#include "util.hpp"

#include "GL/gl.h"

Particle_System::
Particle_System(
    size_t n,
    double charge)
  : n_(n)
  , charge_(charge)
  , particles_(n)
{
}

void
Particle_System::
random_walk(
    System const & system,
    double max_movement,
    double cell_permeability)
{
  Particles::iterator it(particles_.begin());
  Particles::iterator end(particles_.end());

  for(; it != end; ++it)
  {
    it->random_walk(system, max_movement, cell_permeability);
  }
}

void
Particle_System::
draw()
{
  Particles::const_iterator it(particles().begin());
  Particles::const_iterator end(particles().end());

  glBegin(GL_POINTS);
  for (; it != end; ++it)
  {
    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();
}

// TODO: We should keep track of this after every walk, rather than
// recalculating every time
void
Particle_System::
charge_inout_sphere(Point sc, double r, double * in, double * out) const
{
  Particles::const_iterator it(particles().begin());
  Particles::const_iterator end(particles().end());
  
  size_t in_count = 0;
  size_t out_count = 0;

  for (; it != end; ++it)
  {
    bool is_inside = is_inside_sphere(*it, sc, r);
    if (is_inside)
    {
      ++in_count;
    }
    else
    {
      ++out_count;
    }
  }

  *in = in_count * charge_;
  *out = out_count * charge_;
}

