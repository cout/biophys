#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"
#include "Ion_Characteristics.hpp"

#include <GL/glut.h>

#include <cmath>

namespace
{

GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };

}

System::
System()
  : texture_loader_()
  , particle_texture_(texture_loader_.texture("particle.png"))
  , cell_()
  , outer_limit_()
  , sodium_(particle_texture_, 10000)
  , potassium_(particle_texture_, 1000)
  , na_k_pump_()
{
  reset();
}

void
System::
reset()
{
  init_cell();
  init_ions();
  init_temp();
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
init_temp()
{
  temperature_ = 298; // K
}

void
System::
iterate()
{
  sodium_.random_walk(*this, 0.01, cell_.sodium_characteristics);
  potassium_.random_walk(*this, 0.01, cell_.potassium_characteristics);
}

void
System::
draw()
{
  // -- Outer limit --
  GLfloat outer_color[] = { 0.5f, 0.5f, 0.5f, 0.5f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, outer_color);

  glPushMatrix();
  glTranslatef(outer_limit_.x, outer_limit_.y, outer_limit_.z);
  glutWireSphere(outer_limit_.radius, 50, 20);
  glPopMatrix();

  // -- Cell --

  GLfloat cell_color[] = { 0.5f, 0.5f, 0.8f, 0.5f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cell_color);

  // glDisable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(cell_.x, cell_.y, cell_.z);
  // glutSolidSphere(cell_.radius, 75, 50);
  glutWireSphere(cell_.radius, 75, 50);
  glPopMatrix();
  // glEnable(GL_DEPTH_TEST);

  // -- Ions --
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sodium_color);
  sodium_.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, potassium_color);
  potassium_.draw();
}

bool
System::
valid_walk(Ion p, Point dest, Ion_Characteristics & ion_characteristics) const
{
  if (ray_intersects_sphere(p, dest, cell_, cell_.radius))
  {
    return random_double() < ion_characteristics.cell_permeability;
  }

  if (ray_intersects_sphere(p, dest, outer_limit_, outer_limit_.radius))
  {
    return false;
  }

  return true;
}

double
System::
voltage() const
{
  return 0.0; // TODO
}

