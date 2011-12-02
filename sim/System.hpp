#ifndef System__hpp_
#define System__hpp_

#include "Parameters.hpp"
#include "Texture_Loader.hpp"
#include "Texture.hpp"
#include "Cell.hpp"
#include "Particles.hpp"
#include "Point.hpp"
#include "Na_K_Pump.hpp"
#include "Time.hpp"

class System
{
public:
  System(Parameters const & params);

  void reset();
  void iterate(Time const & tv);
  void draw();

  template<typename Particle_T>
  void try_walk(Particle_T & particle, Point dest);

  Cell const & cell() const { return cell_; }
  Na_K_Pump const & na_k_pump() const { return na_k_pump_; }

private:
  void init_cell();
  void init_outer_limit();

  template<typename Particle_T>
  void init_particles(
      Particles<Particle_T> & particles,
      size_t in,
      size_t out,
      int mass);

  void init_particles();

  void init_temp();

  void apply_stimulus_current(Time const & dt);

private:
  Parameters params_;
  Time now_;
  Texture_Loader texture_loader_;
  Texture particle_texture_;
  Cell cell_;
  Cell outer_limit_;
  double temperature_;
  Particles<Sodium_Particle> sodium_;
  Particles<Potassium_Particle> potassium_;
  Na_K_Pump na_k_pump_;
};

#include "System.ipp"

#endif // System__hpp_
