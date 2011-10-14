#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"
#include "Ion_impl.hpp"
#include "Parameters.hpp"

#include <GL/glut.h>

#include <cmath>

namespace
{

Color sodium_color(0.5, 0.5, 1.0, 1.0);
Color potassium_color(1.0, 0.5, 0.5, 1.0);

}

System::
System(Parameters const & params)
  : params_(params)
  , texture_loader_()
  , particle_texture_(texture_loader_.texture("particle.png"))
  , cell_()
  , outer_limit_()
  , sodium_(
      sodium_color,
      particle_texture_,
      params_.initial_sodium_in + params_.initial_sodium_out)
  , potassium_(
      potassium_color,
      particle_texture_,
      params_.initial_potassium_in + params_.initial_potassium_out)
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
  cell_.x = params_.cell_center.x;
  cell_.y = params_.cell_center.y;
  cell_.z = params_.cell_center.z;
  cell_.radius = params_.cell_radius;
  cell_.sodium_inside = params_.initial_sodium_in;
  cell_.sodium_outside = params_.initial_sodium_out;
  cell_.potassium_inside = params_.initial_potassium_in;
  cell_.potassium_outside = params_.initial_potassium_out;
  cell_.membrane_voltage = params_.initial_membrane_voltage;
  cell_.membrane_capacitance = params_.membrane_capacitance;
}

void
System::
init_outer_limit()
{
  outer_limit_.x = params_.cell_center.x;
  outer_limit_.y = params_.cell_center.y;
  outer_limit_.z = params_.cell_center.z;
  outer_limit_.radius = params_.outer_radius;
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
  temperature_ = params_.temperature;
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
  // glutWireSphere(outer_limit_.radius, 40, 15);
  glPopMatrix();

  // -- Cell --

  // GLfloat cell_color[] = { 0.5f, 0.5f, 0.8f, 0.5f };
  GLfloat cell_color[] = { 0.4f, 0.4f, 0.6f, 1.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cell_color);

  // glDisable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(cell_.x, cell_.y, cell_.z);
  // glutSolidSphere(cell_.radius, 75, 50);
  glutWireSphere(cell_.radius, 50, 25);
  glPopMatrix();
  // glEnable(GL_DEPTH_TEST);

  // -- Ions --
  sodium_.draw();
  potassium_.draw();
}

