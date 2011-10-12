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
  double charge_inside;
  double charge_outside;
  double membrane_voltage;
  double membrane_capacitance;

  double permeability(Sodium_Ion const &) const { return 0.4; }
  double permeability(Potassium_Ion const &) const { return 0.4; }

  void put_inside(Sodium_Ion const & ion)
  {
    ++sodium_inside;
    charge_inside += ion.charge();
    // TODO: normally we want to multiply first and then divide, but I
    // think this is a case where we want to do the opposite.
    membrane_voltage += ion.charge() / membrane_capacitance;
  }

  void remove_inside(Sodium_Ion const & ion)
  {
    --sodium_inside;
    charge_inside -= ion.charge();
    membrane_voltage -= ion.charge() / membrane_capacitance;
  }

  void put_inside(Potassium_Ion const & ion)
  {
    ++potassium_inside;
    charge_inside += ion.charge();
    membrane_voltage += ion.charge() / membrane_capacitance;
  }

  void remove_inside(Potassium_Ion const & ion)
  {
    --potassium_inside;
    charge_inside -= ion.charge();
    membrane_voltage -= ion.charge() / membrane_capacitance;
  }

  void put_outside(Sodium_Ion const & ion)
  {
    ++sodium_outside;
    charge_outside += ion.charge();
    membrane_voltage -= ion.charge() / membrane_capacitance;
  }

  void remove_outside(Sodium_Ion const & ion)
  {
    --sodium_outside;
    charge_outside -= ion.charge();
    membrane_voltage += ion.charge() / membrane_capacitance;
  }

  void put_outside(Potassium_Ion const & ion)
  {
    ++potassium_outside;
    charge_outside += ion.charge();
    membrane_voltage -= ion.charge() / membrane_capacitance;
  }

  void remove_outside(Potassium_Ion const & ion)
  {
    --potassium_outside;
    charge_outside -= ion.charge();
    membrane_voltage += ion.charge() / membrane_capacitance;
  }
  template<typename Ion_T>
  void move_inside(Ion_T const & ion)
  {
    this->remove_outside(ion);
    this->put_outside(ion);
  }

  template<typename Ion_T>
  void move_outside(Ion_T const & ion)
  {
    this->remove_inside(ion);
    this->put_outside(ion);
  }
};

#endif // Cell__hpp
