#ifndef Cell__hpp
#define Cell__hpp

#include "Sphere.hpp"
#include "Particle.hpp"

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

  double permeability(Sodium_Particle const &) const { return 0.1; }
  double permeability(Potassium_Particle const &) const { return 0.1; }

  void charge_changed(double delta)
  {
    net_charge += delta;
    double surface_area_in_cm2 = surface_area() / 1e8;
    membrane_voltage += delta / membrane_capacitance / surface_area_in_cm2;
  }

  void put_inside(Sodium_Particle & particle)
  {
    ++sodium_inside;
    particle.is_inside_cell = true;
  }

  void remove_inside(Sodium_Particle & particle)
  {
    --sodium_inside;
  }

  void put_inside(Potassium_Particle & particle)
  {
    ++potassium_inside;
    particle.is_inside_cell = true;
  }

  void remove_inside(Potassium_Particle & particle)
  {
    --potassium_inside;
  }

  void put_outside(Sodium_Particle & particle)
  {
    ++sodium_outside;
    particle.is_inside_cell = false;
  }

  void remove_outside(Sodium_Particle & particle)
  {
    --sodium_outside;
  }

  void put_outside(Potassium_Particle & particle)
  {
    ++potassium_outside;
    particle.is_inside_cell = false;
  }

  void remove_outside(Potassium_Particle & particle)
  {
    --potassium_outside;
  }

  template<typename Particle_T>
  void move_inside(Particle_T & particle)
  {
    this->remove_outside(particle);
    this->put_inside(particle);
    charge_changed(particle.charge());
  }

  template<typename Particle_T>
  void move_outside(Particle_T & particle)
  {
    this->remove_inside(particle);
    this->put_outside(particle);
    charge_changed(-particle.charge());
  }
};

#endif // Cell__hpp
