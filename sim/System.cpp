#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"
#include "Ion_impl.hpp"

#include <GL/glut.h>

#include <cmath>

namespace
{

Color sodium_color(0.5, 0.5, 1.0, 1.0);
Color potassium_color(1.0, 0.5, 0.5, 1.0);

}

System::
System()
  : texture_loader_()
  , particle_texture_(texture_loader_.texture("particle.png"))
  , cell_()
  , outer_limit_()
  , sodium_(sodium_color, particle_texture_, 30000)
  , potassium_(potassium_color, particle_texture_, 30000)
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

//                                      Interstitial     Glial
//                            Neuron      Fluid       Compartment
// Membrane potential, mV      -69.1         0.0        -87.7
// Na+ concentration, mM        10.0       140.0         30.0
// K+ concentration, mM        133.5         3.5        113.5
// Cl- concentration, mM        10.4       143.5          4.8
// A- concentration, mM        133.1         0.0        138.7
// Relative volume               1.0         0.15        10.0

void
System::
init_cell()
{
  cell_.x = 0.0;
  cell_.y = 0.0;
  cell_.z = 0.0;
  cell_.radius = 1.0; // micrometers
  cell_.sodium_inside = 0;
  cell_.sodium_outside = 0;
  cell_.potassium_inside = 0;
  cell_.potassium_outside = 0;
  cell_.membrane_voltage = -70e-3; // volts
  cell_.membrane_capacitance = 1e-6; // farads / cm²
}

void
System::
init_outer_limit()
{
  outer_limit_.x = 0.0;
  outer_limit_.y = 0.0;
  outer_limit_.z = 0.0;
  outer_limit_.radius = 1.25;
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

double
System::
voltage() const
{
  return 0.0; // TODO
}

