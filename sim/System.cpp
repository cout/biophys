#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"
#include "Ion_impl.hpp"

#include <GL/glut.h>

#include <cmath>

namespace
{

GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };
// GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
// GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };

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
  init_outer_limit();
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
  cell_.sodium_inside = 0;
  cell_.sodium_outside = 0;
  cell_.potassium_inside = 0;
  cell_.potassium_outside = 0;
  cell_.membrane_voltage = -70e-3; // volts
  cell_.membrane_capacitance = 1e-6; // farads
}

void
System::
init_outer_limit()
{
  outer_limit_.x = 0.0;
  outer_limit_.y = 0.0;
  outer_limit_.z = 0.0;
  outer_limit_.radius = 2.0;
}

void
System::
init_ions()
{
  {
    // Put sodium ions outside the cell
    auto it(sodium_.begin());
    auto end(sodium_.end());

    for (; it != end; ++it)
    {
      Point p = random_insphere(cell_.radius, outer_limit_.radius);

      it->x = cell_.x + p.x;
      it->y = cell_.y + p.y;
      it->z = cell_.z + p.z;

      cell_.put_outside(*it);
    }
  }

  {
    // Put potassium ions inside the cell
    auto it = potassium_.begin();
    auto end = potassium_.end();

    for (; it != end; ++it)
    {
      Point p = random_insphere(0, cell_.radius);

      it->x = cell_.x + p.x;
      it->y = cell_.y + p.y;
      it->z = cell_.z + p.z;

      cell_.put_inside(*it);
    }
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
  sodium_.random_walk(*this, 0.01);
  potassium_.random_walk(*this, 0.01);
}

void
System::
draw()
{
  // -- Outer limit --
  // GLfloat outer_color[] = { 0.5f, 0.5f, 0.5f, 0.5f };
  GLfloat outer_color[] = { 0.4f, 0.4f, 0.4f, 1.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, outer_color);

  glPushMatrix();
  glTranslatef(outer_limit_.x, outer_limit_.y, outer_limit_.z);
  glutWireSphere(outer_limit_.radius, 50, 20);
  glPopMatrix();

  // -- Cell --

  // GLfloat cell_color[] = { 0.5f, 0.5f, 0.8f, 0.5f };
  GLfloat cell_color[] = { 0.4f, 0.4f, 0.6f, 1.0f };
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

double
System::
voltage() const
{
  return 0.0; // TODO
}

