#ifndef Na_K_Pump__hpp
#define Na_K_Pump__hpp

class Na_K_Pump
{
public:
  Na_K_Pump(double ratio = 2.0/3.0);

  bool pass_sodium_in();

  bool pass_potassium_out();

private:
  double ratio_;
  double sodium_passed_in_;
  double potassium_passed_out_;
};

#endif // Na_K_Pump__hpp
