#ifndef Na_K_Pump__hpp
#define Na_K_Pump__hpp

#include "Ion.hpp"

class Na_K_Pump
{
public:
  Na_K_Pump(double ratio = 2.0/3.0);

  bool pass_ion(Sodium_Ion const & ion, bool dst_is_inside);
  bool pass_ion(Potassium_Ion const & ion, bool dst_is_inside);

  bool pass_sodium_out();
  bool pass_potassium_in();

  double sodium_pumped() const { return sodium_passed_out_; }
  double potassium_pumped() const { return potassium_passed_in_; }

private:
  double ratio_;
  double sodium_passed_out_;
  double potassium_passed_in_;
};

#endif // Na_K_Pump__hpp
