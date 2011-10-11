#include "Na_K_Pump.hpp"
#include "Ions.hpp"
#include "Cell.hpp"

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
pass_ion(Sodium_Ion const & ion, bool dst_is_inside)
{
  if (!dst_is_inside)
  {
    return pass_sodium_out();
  }
  else
  {
    return false;
  }
}

bool
Na_K_Pump::
pass_ion(Potassium_Ion const & ion, bool dst_is_inside)
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

bool pass_ion(Potassium_Ion const & ion, bool dst_is_inside);

bool
Na_K_Pump::
pass_sodium_out()
{
  double sodium_expected = potassium_passed_in_ / ratio_;
  double r = std::log(sodium_expected - sodium_passed_out_);
  bool passed = std::rand() < r;
  sodium_passed_out_ += (passed ? 1 : 0);
  return passed;
}


bool
Na_K_Pump::
pass_potassium_in()
{
  double potassium_expected = ratio_ * sodium_passed_out_;
  double r = std::log(potassium_expected - potassium_passed_in_);
  bool passed = std::rand() < r;
  potassium_passed_in_ += (passed ? 1 : 0);
  return passed;
}

