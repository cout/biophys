#include "Cell.hpp"
#include "Time.hpp"

Cell::Cell()
  : Sphere()
  , sodium_inside(0)
  , sodium_outside(0)
  , potassium_inside(0)
  , potassium_outside(0)
  , net_charge(0)
  , membrane_voltage(0)
  , membrane_capacitance(0)
  , n(0)
  , m(0)
  , h(0)
{
}

void
Cell::
update_permeabilities(Time const & dt)
{
  double phi = 1;

  double v = membrane_voltage;

  double gnabar = 120.0;
  double gkbar = 36.0;

  double am = phi * 0.1 * (v+40) / (1-exp(-(v+40)/10));
  double bm = phi * 4 * exp(-(v+65)/18);
  double dm = dt * (am*(1-m) - bm*m);

  double ah = phi * 0.07 * exp(-(v+65)/20);
  double bh = phi * 1.0 / (1+exp(-(v+35)/10));
  double dh = dt * (ah*(1-h) - bh*h);

  double an = phi * 0.01 * (v+55) / (1-exp(-(v+55)/10));
  double bn = phi * 0.125 * exp(-(v+65)/80);
  double dn = dt * (an*(1-n) - bn*n);

  m += dm;
  h += dh;
  n += dn;

  double gna = gnabar * ipow(m, 3) * h;
  double gk = gkbar * ipow(n, 4);

  // TODO: conductance and permeability aren't quite the same
  sodium_permeability = gna;
  potassium_permeability = gk;
}

void
Cell::
charge_changed(double delta)
{
  net_charge += delta;
  double surface_area_in_cm2 = surface_area() / 1e8;
  double voltage_delta = delta / membrane_capacitance / surface_area_in_cm2;

  // TODO: repeated addition like this will result in numerical error
  membrane_voltage += voltage_delta;
}

