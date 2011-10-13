#ifndef Cell__hpp
#define Cell__hpp

#include "Sphere.hpp"
#include "Ion.hpp"

class Cell
  : public Sphere
{
public:
  Cell();

  double sodium_inside;
  double sodium_outside;
  double potassium_inside;
  double potassium_outside;
  double net_charge;
  double membrane_voltage;
  double membrane_capacitance;

  double permeability(Sodium_Ion const &) const { return 0.1; }
  double permeability(Potassium_Ion const &) const { return 0.1; }

  void charge_changed(double delta)
  {
    net_charge += delta;
    double surface_area_in_cm2 = surface_area() / 1e8;
    membrane_voltage += delta / membrane_capacitance / surface_area_in_cm2;
  }

  void put_inside(Sodium_Ion const & ion)
  {
    ++sodium_inside;
  }

  void remove_inside(Sodium_Ion const & ion)
  {
    --sodium_inside;
  }

  void put_inside(Potassium_Ion const & ion)
  {
    ++potassium_inside;
  }

  void remove_inside(Potassium_Ion const & ion)
  {
    --potassium_inside;
  }

  void put_outside(Sodium_Ion const & ion)
  {
    ++sodium_outside;
  }

  void remove_outside(Sodium_Ion const & ion)
  {
    --sodium_outside;
  }

  void put_outside(Potassium_Ion const & ion)
  {
    ++potassium_outside;
  }

  void remove_outside(Potassium_Ion const & ion)
  {
    --potassium_outside;
  }

  template<typename Ion_T>
  void move_inside(Ion_T const & ion)
  {
    this->remove_outside(ion);
    this->put_inside(ion);
    charge_changed(ion.charge());
  }

  template<typename Ion_T>
  void move_outside(Ion_T const & ion)
  {
    this->remove_inside(ion);
    this->put_outside(ion);
    charge_changed(-ion.charge());
  }
};

#endif // Cell__hpp
