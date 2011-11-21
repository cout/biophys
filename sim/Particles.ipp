#include "Particles.hpp"

#include "GL/gl.h"
#include "GL/glext.h"

template <typename Particle_T>
Particles<Particle_T>::
Particles(
    Color color,
    Texture texture,
    size_t n)
  : color_(color)
  , texture_(texture)
  , particles_(n)
{
}

template <typename Particle_T>
void
Particles<Particle_T>::
random_walk(
    System & system,
    double max_movement)
{
  iterator it(this->begin());
  iterator end(this->end());

  for(; it != end; ++it)
  {
    it->random_walk(system, max_movement);
  }
}

template <typename Particle_T>
void
Particles<Particle_T>::
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

  glDisable(GL_LIGHTING);

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
    if (it->is_inside_cell)
    {
      glColor4d(color_.r * 0.4, color_.g * 0.4, color_.b * 0.4, color_.a);
    }
    else
    {
      glColor4d(color_.r, color_.g, color_.b, color_.a);
    }

    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();

  glDisable(GL_POINT_SPRITE_ARB);

  // glDepthMask(GL_TRUE);
  // glDisable(GL_ALPHA_TEST);

  glPopAttrib();
}

