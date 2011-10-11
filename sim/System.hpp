#ifndef System__hpp_
#define System__hpp_

#include "Texture_Loader.hpp"
#include "Texture.hpp"
#include "Cell.hpp"
#include "Ions.hpp"
#include "Point.hpp"
#include "Na_K_Pump.hpp"

class Ion_Characteristics;

class System
{
public:
  System();

  void reset();
  void iterate();
  void draw();

  template<typename Ion_T>
  void try_walk(Ion_T & ion, Point dest) const;

  double voltage() const;

  Cell const & cell() const { return cell_; }
  Na_K_Pump const & na_k_pump() const { return na_k_pump_; }

private:
  void init_cell();
  void init_ions();
  void init_temp();

private:
  Texture_Loader texture_loader_;
  Texture particle_texture_;
  Cell cell_;
  Cell outer_limit_;
  double temperature_;
  Ions<Sodium_Ion> sodium_;
  Ions<Potassium_Ion> potassium_;
  Na_K_Pump na_k_pump_;
};

#include "System.ipp"

#endif // System__hpp_
