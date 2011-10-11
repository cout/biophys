#include "util.hpp"

template<typename Ion_T>
void
System::
try_walk(Ion_T & ion, Point dest) const
{
  bool src_is_inside(is_inside_sphere(ion, cell_, cell_.radius));
  bool dst_is_inside(is_inside_sphere(dest, cell_, cell_.radius));

  // Crossing the cell membrane happens with a probability equal to the
  // permeability
  if (src_is_inside != dst_is_inside)
  {
    if(random_double() < cell_.permeability(ion))
    {
      goto walk;
    }
    else
    {
      return;
    }
  }

  // Crossing the outer limit happens with zero probability
  if (ray_intersects_sphere(ion, dest, outer_limit_, outer_limit_.radius))
  {
    return;
  }

walk:
  // ion_characteristics.ions_inside_cell -= (src_is_inside ? 1 : 0);
  // ion_characteristics.ions_outside_cell -= (src_is_inside ? 0 : 1);

  ion.move_to(dest);

  // ion_characteristics.ions_inside_cell += (dst_is_inside ? 1 : 0);
  // ion_characteristics.ions_outside_cell += (dst_is_inside ? 0 : 1);
}

