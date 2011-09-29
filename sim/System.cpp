#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"

#include <GL/glut.h>

namespace
{

GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };

}

System::
System()
  : cell_()
  , outer_limit_()
  , sodium_(10000)
  , potassium_(1000)
{
  reset();
}

void
System::
reset()
{
  init_cell();
  init_ions();
}

void
System::
init_cell()
{
  cell_.x = 0.0;
  cell_.y = 0.0;
  cell_.z = 0.0;
  cell_.radius = 1.0;

  outer_limit_.x = 0.0;
  outer_limit_.y = 0.0;
  outer_limit_.z = 0.0;
  outer_limit_.radius = 2.0;
}

void
System::
init_ions()
{
  // Put sodium ions outside the cell
  Particle_System::Particles::iterator it(sodium_.particles().begin());
  Particle_System::Particles::iterator end(sodium_.particles().end());

  for (; it != end; ++it)
  {
    Point p = random_insphere(cell_.radius, outer_limit_.radius);

    it->x = cell_.x + p.x;
    it->y = cell_.y + p.y;
    it->z = cell_.z + p.z;
  }

  // Put potassium ions inside the cell
  it = potassium_.particles().begin();
  end = potassium_.particles().end();

  for (; it != end; ++it)
  {
    Point p = random_insphere(0, cell_.radius);

    it->x = cell_.x + p.x;
    it->y = cell_.y + p.y;
    it->z = cell_.z + p.z;
  }
}

void
System::
iterate()
{
  sodium_.random_walk(*this, 0.01, 0.0);
  potassium_.random_walk(*this, 0.01, 0.0);
}

void
System::
draw()
{
  // -- Ions --

  glPointSize(2.0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sodium_color);
  sodium_.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, potassium_color);
  potassium_.draw();

  // -- Cell --

  GLfloat cell_color[] = { 0.5f, 0.5f, 0.8f, 0.5f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cell_color);

  glPushMatrix();
  glTranslatef(cell_.x, cell_.y, cell_.z);
  glutSolidSphere(cell_.radius, 50, 20);
  glPopMatrix();

  // -- Outer limit --
  GLfloat outer_color[] = { 0.5f, 0.5f, 0.5f, 0.5f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, outer_color);

  glPushMatrix();
  glTranslatef(outer_limit_.x, outer_limit_.y, outer_limit_.z);
  glutWireSphere(outer_limit_.radius, 50, 20);
  glPopMatrix();
}

bool
System::
valid_walk(Particle p, Point dest, double cell_permeability) const
{
  return true;
}

