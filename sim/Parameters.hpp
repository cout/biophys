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
    : time_stretch(1000.0)
    , cell_center(0, 0, 0)
    , cell_radius(1.0)
    , outer_radius(1.25)
    , initial_membrane_voltage(-70e-3)
    , membrane_capacitance(1e-6)
    , temperature(298)
    , initial_sodium_in(3000)
    , initial_sodium_out(14000)
    , initial_potassium_in(11350)
    , initial_potassium_out(3500)
    , sodium_mass(100)
    , potassium_mass(100)
    , sodium_velocity(500.0)
    , potassium_velocity(500.0)
    , stim_delay(0.005)
    , stim_duration(0.001)
    , stim_current(30e-9)
  {
  }

  double time_stretch;

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

  int sodium_mass; // unspecified units
  int potassium_mass; // unspecified units

  double sodium_velocity; // unspecified units
  double potassium_velocity; // unspecified units

  // stimulus current
  double stim_delay;    // seconds
  double stim_duration; // seconds
  double stim_current;  // amps / cm² ?
};

#endif // Parameters__hpp
