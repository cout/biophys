#include "util.hpp"

template<typename Ion_T>
void
System::
try_walk(Ion_T & ion, Point dest)
{
  bool src_is_inside(ion.is_inside_cell);
  bool dst_is_inside(is_inside_sphere(dest, cell_));

  // Optimization for intracellular movement
  if (src_is_inside && dst_is_inside)
  {
    goto walk;
  }

  // Crossing the cell membrane happens with a probability equal to the
  // permeability
  if (src_is_inside != dst_is_inside)
  {
    if(random_double() < cell_.permeability(ion))
    {
      goto crosswalk;
    }
    else if (na_k_pump_.pass_ion(ion, dst_is_inside))
    {
      goto crosswalk;
    }
    else
    {
      return;
    }
  }

  // Crossing the outer limit happens with zero probability
  if (ray_intersects_sphere(ion, dest, outer_limit_))
  {
    return;
  }

  goto walk;

crosswalk:
  if (dst_is_inside)
  {
    cell_.move_inside(ion);
  }
  else
  {
    cell_.move_outside(ion);
  }

walk:
  ion.move_to(dest);
}

