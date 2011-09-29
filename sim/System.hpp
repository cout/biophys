#ifndef System__hpp_
#define System__hpp_

#include "Cell.hpp"
#include "Particle_System.hpp"
#include "Point.hpp"

class System
{
public:
  System();

  void reset();
  void iterate();
  void draw();

  bool valid_walk(Particle p, Point dest, double cell_permeability) const;

private:
  void init_cell();
  void init_ions();

private:
  Cell cell_;
  Cell outer_limit_;
  Particle_System sodium_;
  Particle_System potassium_;
};

#endif // System__hpp_
