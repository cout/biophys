#include "Ions.hpp"

#include "GL/gl.h"
#include "GL/glext.h"

Ions::
Ions(
    Texture texture,
    size_t n)
  : texture_(texture)
  , ions_(n)
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
  glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);

  GLfloat sizes[2];
  glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes);
  glPointParameterfARB(GL_POINT_SIZE_MAX_ARB, sizes[1]);
  glPointParameterfARB(GL_POINT_SIZE_MIN_ARB, sizes[0]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexEnvf(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
  glEnable(GL_POINT_SPRITE_ARB);

  GLfloat quadratic[] = { 1.0, 0.0, 0.0 };
  glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic); // TODO: slow

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_.texture);

  glPointSize(8.0);

  iterator it(this->begin());
  iterator end(this->end());

  // glDepthMask(GL_FALSE);
  glBegin(GL_POINTS);
  for (; it != end; ++it)
  {
    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();

  glDisable(GL_POINT_SPRITE_ARB);

  // glDepthMask(GL_TRUE);

  glPopAttrib();
}

