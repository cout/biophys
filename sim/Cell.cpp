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
  double const phi = 1;

  double const v = membrane_voltage;

  double const gnabar = 120.0; // mS/cm²
  double const gkbar = 36.0; // mS/cm²

  int const steps = 16384;

  for (int j = 0; j < steps; ++j)
  {
    double am = phi * 0.1 * (v+40) / (1-exp(-(v+40)/10));
    double bm = phi * 4 * exp(-(v+65)/18);
    double dm = (dt / steps) * (am*(1-m) - bm*m);

    double ah = phi * 0.07 * exp(-(v+65)/20);
    double bh = phi * 1.0 / (1+exp(-(v+35)/10));
    double dh = (dt / steps) * (ah*(1-h) - bh*h);

    double an = phi * 0.01 * (v+55) / (1-exp(-(v+55)/10));
    double bn = phi * 0.125 * exp(-(v+65)/80);
    double dn = (dt / steps) * (an*(1-n) - bn*n);

    m += dm * 1000; // TODO: why?
    h += dh * 1000; // TODO: why?
    n += dn * 1000; // TODO: why?
  }

  double gna = gnabar * ipow(m, 3) * h; // mS/cm²
  double gk = gkbar * ipow(n, 4); // mS/cm²

  // TODO: conductance and permeability aren't quite the same
  sodium_permeability = gna;
  potassium_permeability = gk;
}

void
Cell::
charge_changed(double charge_delta)
{
  net_charge += charge_delta;

  double surface_area_in_cm2 = surface_area() / 1e8;
  double voltage_delta = charge_delta / membrane_capacitance / surface_area_in_cm2;

  // TODO: repeated addition like this will result in numerical error
  membrane_voltage += voltage_delta * 1000.0;
}

void
Cell::
apply_stimulus_current(
    double current,
    Time const & dt)
{
  double voltage_delta = dt * current / membrane_capacitance;
  membrane_voltage += voltage_delta * 1000 * 1000;
}

