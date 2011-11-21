#include "util.hpp"

template<typename Derived_T, int Charge>
template<typename System_T>
void
Particle_T<Derived_T, Charge>::
random_walk(
    System_T & system,
    double max_movement)
{
  Point p = random_insphere(0, max_movement);
  p.x += this->x;
  p.y += this->y;
  p.z += this->z;

  system.try_walk(static_cast<Derived_T &>(*this), p);
}

