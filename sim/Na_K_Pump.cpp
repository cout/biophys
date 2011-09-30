#include "Na_K_Pump.hpp"
#include "Ions.hpp"
#include "Cell.hpp"

Na_K_Pump::
Na_K_Pump()
{
}


void
Na_K_Pump::
pump(
    Ions & sodium,
    Ions & potassium,
    Cell const & cell)
{
  // Pick a random point on the cell
  // Find nearby 3 sodium ions
  // Find nearby 2 potassium ions
  // Swap positions of ions; 3rd sodium ion gets placed at the midpoint
  // of the other 2
}


