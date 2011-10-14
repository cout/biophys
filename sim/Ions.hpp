#ifndef Ions__hpp_
#define Ions__hpp_

#include "Color.hpp"
#include "Texture.hpp"
#include "Ion.hpp"

#include <vector>

template <typename Ion_T>
class Ions
{
public:
  Ions(
      Color color,
      Texture texture,
      size_t n);

  void random_walk(
      System & system,
      double max_movement);

  typedef std::vector<Ion_T> Container;
  typedef typename Container::iterator iterator;
  typedef typename Container::const_iterator const_iterator;

  iterator begin() { return ions_.begin(); }
  const_iterator begin() const { return ions_.begin(); }

  iterator end() { return ions_.end(); }
  const_iterator end() const { return ions_.end(); }

  void draw();

private:
  Color color_;
  Texture texture_;
  Container ions_;
};

#include "Ions.ipp"

#endif // Ions__hpp_

