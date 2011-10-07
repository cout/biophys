#ifndef Ion_Characteristics__hpp
#define Ion_Characteristics__hpp

#include <cstdlib>

class Ion_Characteristics
{
public:
  Ion_Characteristics(
      double cell_permeability,
      size_t ions_inside_cell,
      size_t ions_outside_cell)
    : cell_permeability(cell_permeability)
    , ions_inside_cell(ions_inside_cell)
    , ions_outside_cell(ions_outside_cell)
  {
  }

  double cell_permeability;
  size_t ions_inside_cell;
  size_t ions_outside_cell;
};

#endif // Ion_Characteristics__hpp
