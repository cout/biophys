#include "Cell.hpp"

Cell::Cell()
  : Sphere()
  , sodium_inside(0)
  , sodium_outside(0)
  , potassium_inside(0)
  , potassium_outside(0)
  , net_charge(0)
  , membrane_voltage(0)
  , membrane_capacitance(0)
{
}

