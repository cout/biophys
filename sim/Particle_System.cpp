#include "Particle_System.hpp"

#include "GL/gl.h"

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

