#include "Ions.hpp"

#include "GL/gl.h"
#include "GL/glext.h"

template <typename Ion_T>
Ions<Ion_T>::
Ions(
    Texture texture,
    size_t n)
  : texture_(texture)
  , ions_(n)
{
}

template <typename Ion_T>
void
Ions<Ion_T>::
random_walk(
    System const & system,
    double max_movement)
{
  iterator it(this->begin());
  iterator end(this->end());

  for(; it != end; ++it)
  {
    it->random_walk(system, max_movement);
  }
}

template <typename Ion_T>
void
Ions<Ion_T>::
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
  glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic); // TODO: slow?

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_.texture);

  glPointSize(8.0);
  // glPointSize(6.0);

  iterator it(this->begin());
  iterator end(this->end());

  // glAlphaFunc(GL_GREATER, 0.1);
  // glEnable(GL_ALPHA_TEST);
  // glDepthMask(GL_FALSE);

  glBegin(GL_POINTS);
  for (; it != end; ++it)
  {
    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();

  glDisable(GL_POINT_SPRITE_ARB);

  // glDepthMask(GL_TRUE);
  // glDisable(GL_ALPHA_TEST);

  glPopAttrib();
}

