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

  void try_walk(Ion & ion, Point dest, Ion_Characteristics & cell_permeability) const;

  double voltage() const;

  Cell const & cell() const { return cell_; }

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
  Ions sodium_;
  Ions potassium_;
  Na_K_Pump na_k_pump_;
};

#endif // System__hpp_
