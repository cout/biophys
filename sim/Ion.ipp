#include "System.hpp"
#include "util.hpp"

template<typename Derived_T>
void
Ion_T<Derived_T>::
random_walk(
    System & system,
    double max_movement)
{
  Point p = random_insphere(0, max_movement);
  p.x += x;
  p.y += y;
  p.z += z;

  system.try_walk(static_cast<Derived_T &>(*this), p);
}

