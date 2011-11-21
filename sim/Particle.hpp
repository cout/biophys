#ifndef Particle__hpp
#define Particle__hpp

#include "Point.hpp"

class System;
class Particle_Characteristics;

class Particle
  : public Point
{
public:
  Particle()
    : Point(0, 0, 0)
  {
  }

  bool is_inside_cell;
};

template<typename Derived_T, int Charge>
class Particle_T
  : public Particle
{
public:
  template<typename System_T>
  void random_walk(
      System_T & system,
      double max_movement);

  static double const ELEMENTARY_CHARGE = 1.602176565e-19;

  double charge() const
  {
    return 10 * Charge * ELEMENTARY_CHARGE;
  }
};

class Sodium_Particle
  : public Particle_T<Sodium_Particle, 1>
{
};

class Potassium_Particle
  : public Particle_T<Potassium_Particle, 1>
{
};

#include "Particle.ipp"

#endif // Particle__hpp
