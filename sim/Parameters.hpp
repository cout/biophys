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
    , initial_membrane_voltage(-70)
    , membrane_capacitance(1)
    , initial_sodium_in(6000)
    , initial_sodium_out(28000)
    , initial_potassium_in(22700)
    , initial_potassium_out(7000)
    , sodium_mass(500000) // TODO: fudge
    , potassium_mass(500000) // TODO: fudge
    , sodium_velocity(500.0)
    , potassium_velocity(500.0)
    , stim_delay(0.005)
    , stim_duration(0.001)
    , stim_current(30)
    , n_initial(0)
    , m_initial(1)
    , h_initial(0)
  {
  }

  double time_stretch;

  Point cell_center; // micrometers
  double cell_radius; // micrometers
  double outer_radius; // micrometers

  double initial_membrane_voltage; // mV
  double membrane_capacitance; // uF / cm²

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
  double stim_current;  // nA / cm² ?

  double n_initial; // no units
  double m_initial; // no units
  double h_initial; // no units
};

#endif // Parameters__hpp
