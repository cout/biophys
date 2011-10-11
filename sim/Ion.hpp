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

template<typename Derived_T>
class Ion_T
  : public Ion
{
public:
  void random_walk(
      System const & system,
      double max_movement);
};

class Sodium_Ion
  : public Ion_T<Sodium_Ion>
{
};

class Potassium_Ion
  : public Ion_T<Potassium_Ion>
{
};

#endif // Ion__hpp
