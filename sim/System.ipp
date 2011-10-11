#include "util.hpp"

template<typename Ion_T>
void
System::
try_walk(Ion_T & ion, Point dest)
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
    else if (na_k_pump_.pass_ion(ion, dst_is_inside))
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
  ion.move_to(dest);

  if (src_is_inside != dst_is_inside)
  {
    if (dst_is_inside)
    {
      cell_.move_inside(ion);
    }
    else
    {
      cell_.move_outside(ion);
    }
  }
}

