#ifndef Parameters__hpp
#define Parameters__hpp

#include "Point.hpp"

//                                      Interstitial     Glial
//                            Neuron      Fluid       Compartment
// Membrane potential, mV      -69.1         0.0        -87.7
// Na+ concentration, mM        10.0       140.0         30.0
// K+ concentration, mM        133.5         3.5        113.5
// Cl- concentration, mM        10.4       143.5          4.8
// A- concentration, mM        133.1         0.0        138.7
// Relative volume               1.0         0.15        10.0

class Parameters
{
public:
  Parameters()
    : cell_center(0, 0, 0)
    , cell_radius(1.0)
    , outer_radius(1.25)
    , initial_membrane_voltage(-70e-3)
    , membrane_capacitance(1e-6)
    , temperature(298)
    , initial_sodium_in(0)
    , initial_sodium_out(30000)
    , initial_potassium_in(30000)
    , initial_potassium_out(0)
    , sodium_velocity(0.1)
    , potassium_velocity(0.1)
  {
  }

  Point cell_center; // micrometers
  double cell_radius; // micrometers
  double outer_radius; // micrometers

  double initial_membrane_voltage; // volts
  double membrane_capacitance; // farads / cm²

  double temperature; // Kelvins

  double initial_sodium_permeability;
  double initial_potassium_permeability;
  double initial_sodium_in;
  double initial_sodium_out;
  double initial_potassium_in;
  double initial_potassium_out;

  double sodium_velocity;
  double potassium_velocity;
};

#endif // Parameters__hpp
