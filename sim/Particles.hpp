#ifndef Particles__hpp_
#define Particles__hpp_

#include "Color.hpp"
#include "Texture.hpp"
#include "Particle.hpp"

#include <vector>

template <typename Particle_T>
class Particles
{
public:
  Particles(
      Color color,
      Texture texture,
      size_t n);

  void random_walk(
      System & system,
      double max_movement);

  typedef std::vector<Particle_T> Container;
  typedef typename Container::iterator iterator;
  typedef typename Container::const_iterator const_iterator;

  iterator begin() { return particles_.begin(); }
  const_iterator begin() const { return particles_.begin(); }

  iterator end() { return particles_.end(); }
  const_iterator end() const { return particles_.end(); }

  void draw();

private:
  Color color_;
  Texture texture_;
  Container particles_;
};

#include "Particles.ipp"

#endif // Particles__hpp_

