#include "Na_K_Pump.hpp"
#include "Ions.hpp"
#include "Cell.hpp"

#include <cstdlib>

Na_K_Pump::
Na_K_Pump(double ratio)
  : ratio_(ratio)
  , sodium_passed_in_(0)
  , potassium_passed_out_(0)
{
}


bool
Na_K_Pump::
pass_sodium_in()
{
  double sodium_expected = potassium_passed_out_ / ratio;
  double r = log(sodium_expected - sodium_passed_in_);
  bool passed = std::rand() < r;
  sodium_passed_in_ += (passed ? 1 : 0);
  return passed;
}


bool
Na_K_Pump::
pass_potassium_out()
{
  double potassium_expected = ratio * sodium_passed_in_;
  double r = log(potassium_expected - potassium_passed_out_);
  bool passed = std::rand() < r;
  potassium_passed_out_ += (passed ? 1 : 0);
  return passed;
}

