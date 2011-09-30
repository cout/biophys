#ifndef Ions__hpp_
#define Ions__hpp_

#include "Ion.hpp"

#include <vector>

class Ions
{
public:
  Ions(size_t n);

  void random_walk(
      System const & system,
      double max_movement,
      double cell_permeability);

  typedef std::vector<Ion> Container;
  typedef Container::iterator iterator;
  typedef Container::const_iterator const_iterator;

  iterator begin() { return ions_.begin(); }
  const_iterator begin() const { return ions_.begin(); }

  iterator end() { return ions_.end(); }
  const_iterator end() const { return ions_.end(); }

  void draw();

private:
  Container ions_;
};

#endif // Ions__hpp_

