#ifndef Ions__hpp_
#define Ions__hpp_

#include "Texture.hpp"
#include "Ion.hpp"

#include <vector>

class Ion_Characteristics;

class Ions
{
public:
  Ions(
      Texture texture,
      size_t n);

  void random_walk(
      System const & system,
      double max_movement,
      Ion_Characteristics & ion_characteristics);

  typedef std::vector<Ion> Container;
  typedef Container::iterator iterator;
  typedef Container::const_iterator const_iterator;

  iterator begin() { return ions_.begin(); }
  const_iterator begin() const { return ions_.begin(); }

  iterator end() { return ions_.end(); }
  const_iterator end() const { return ions_.end(); }

  void draw();

private:
  Texture texture_;
  Container ions_;
};

#endif // Ions__hpp_

