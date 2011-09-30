#include "Ions.hpp"

#include "GL/gl.h"

Ions::
Ions(size_t n)
  : ions_(n)
{
}

void
Ions::
random_walk(
    System const & system,
    double max_movement,
    double cell_permeability)
{
  iterator it(this->begin());
  iterator end(this->end());

  for(; it != end; ++it)
  {
    it->random_walk(system, max_movement, cell_permeability);
  }
}

void
Ions::
draw()
{
  iterator it(this->begin());
  iterator end(this->end());

  glBegin(GL_POINTS);
  for (; it != end; ++it)
  {
    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();
}

