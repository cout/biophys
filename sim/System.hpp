#ifndef System__hpp_
#define System__hpp_

#include "Cell.hpp"
#include "Ions.hpp"
#include "Point.hpp"
#include "Na_K_Pump.hpp"

class System
{
public:
  System();

  void reset();
  void iterate();
  void draw();

  bool valid_walk(Ion p, Point dest, double cell_permeability) const;

private:
  void init_cell();
  void init_ions();

private:
  Cell cell_;
  Cell outer_limit_;
  Ions sodium_;
  Ions potassium_;
  Na_K_Pump na_k_pump_;
};

#endif // System__hpp_
