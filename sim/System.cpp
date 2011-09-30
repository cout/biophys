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
  cell_.sodium_permeability = 0.4;
  cell_.potassium_permeability = 0.4;

  outer_limit_.x = 0.0;
  outer_limit_.y = 0.0;
  outer_limit_.z = 0.0;
  outer_limit_.radius = 2.0;
  outer_limit_.sodium_permeability = 0.0;
  outer_limit_.potassium_permeability = 0.0;
}

void
System::
init_ions()
{
  // Put sodium ions outside the cell
  Ions::iterator it(sodium_.begin());
  Ions::iterator end(sodium_.end());

  for (; it != end; ++it)
  {
    Point p = random_insphere(cell_.radius, outer_limit_.radius);

    it->x = cell_.x + p.x;
    it->y = cell_.y + p.y;
    it->z = cell_.z + p.z;
  }

  // Put potassium ions inside the cell
  it = potassium_.begin();
  end = potassium_.end();

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
  sodium_.random_walk(*this, 0.01, cell_.sodium_permeability);
  potassium_.random_walk(*this, 0.01, cell_.potassium_permeability);
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
valid_walk(Ion p, Point dest, double cell_permeability) const
{
  if (ray_intersects_sphere(p, dest, cell_, cell_.radius))
  {
    return random_double() < cell_permeability;
  }

  if (ray_intersects_sphere(p, dest, outer_limit_, outer_limit_.radius))
  {
    return false;
  }

  return true;
}

