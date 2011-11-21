#include "Na_K_Pump.hpp"
#include "Particles.hpp"
#include "Cell.hpp"
#include "util.hpp"

#include <cstdlib>
#include <cmath>

Na_K_Pump::
Na_K_Pump(double ratio)
  : ratio_(ratio)
  , sodium_passed_out_(0)
  , potassium_passed_in_(0)
{
}


bool
Na_K_Pump::
pass_particle(Sodium_Particle const & particle, bool dst_is_inside)
{ if (!dst_is_inside) {
    return pass_sodium_out();
  }
  else
  {
    return false;
  }
}

bool
Na_K_Pump::
pass_particle(Potassium_Particle const & particle, bool dst_is_inside)
{
  if (dst_is_inside)
  {
    return pass_potassium_in();
  }
  else
  {
    return false;
  }
}

#include <iostream>

bool
Na_K_Pump::
pass_sodium_out()
{
  double sodium_expected = potassium_passed_in_ / ratio_;
  double r = std::log(2 + sodium_expected - sodium_passed_out_);
  bool passed = random_double() < r;
  sodium_passed_out_ += (passed ? 1 : 0);
  return passed;
}


bool
Na_K_Pump::
pass_potassium_in()
{
  double potassium_expected = ratio_ * sodium_passed_out_;
  double r = std::log(2 + potassium_expected - potassium_passed_in_);
  bool passed = random_double() < r;
  potassium_passed_in_ += (passed ? 1 : 0);
  return passed;
}

