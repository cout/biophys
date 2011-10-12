#ifndef Ion__hpp
#define Ion__hpp

#include "Point.hpp"

class System;
class Ion_Characteristics;

class Ion
  : public Point
{
public:
  Ion()
    : Point(0, 0, 0)
  {
  }
};

template<typename Derived_T, int Charge>
class Ion_T
  : public Ion
{
public:
  void random_walk(
      System & system,
      double max_movement);

  static double const ELEMENTARY_CHARGE = 1.602176565e-19;

  double charge() const
  {
    return Charge * ELEMENTARY_CHARGE;
  }
};

class Sodium_Ion
  : public Ion_T<Sodium_Ion, 1>
{
};

class Potassium_Ion
  : public Ion_T<Potassium_Ion, 1>
{
};

#endif // Ion__hpp
