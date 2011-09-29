#include "System.hpp"
#include "Point.hpp"
#include "util.hpp"

#include <GL/glut.h>

#include <cmath>

namespace
{

GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };

}

System::
System()
  : cell_()
  , outer_limit_()
  , sodium_(10000, 1.0)
  , potassium_(1000, 1.0)
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
  cell_.sodium_permeability = 0.0;
  cell_.potassium_permeability = 0.0;

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
init_temp()
{
  temperature_ = 298; // K
}

void
System::
iterate()
{
  // TODO: Ideally we should use the Nernst-Planck equation to describe
  // the movement of ions, rather than doing a random walk.  With the
  // random walk the ions follow Fick's law of diffusion, but are not
  // affected by the electrostatic force.
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
valid_walk(Particle p, Point dest, double cell_permeability) const
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

double
System::
voltage() const
{
  double sodium_in, sodium_out;
  double potassium_in, potassium_out;

  sodium_.charge_inout_sphere(cell_, cell_.radius, &sodium_in, &sodium_out);
  potassium_.charge_inout_sphere(cell_, cell_.radius, &potassium_in, &potassium_out);

  // TODO: is it acceptable to use probability here instead of measuring
  // permeability in m/s?
  double K = (sodium_out * cell_.sodium_permeability + potassium_out * cell_.potassium_permeability) /
             (sodium_in * cell_.sodium_permeability + potassium_in * cell_.potassium_permeability);

  // GHK voltage
  double R = 8.31444621; // J/(mol*K)
  double T = temperature_; // K
  double F = 96485.3365; // C/mol
  double E_m = (R * T / F) * std::log(K);

  return E_m;
}

