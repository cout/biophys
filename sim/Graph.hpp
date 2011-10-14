#ifndef Graph__hpp
#define Graph__hpp

#include <vector>

class Graph
{
public:
  Graph();

  void add_point(double t, double val);

  void draw();

private:
  typedef std::vector<std::pair<double, double> > Values;
  Values values_;
};

#endif // Graph__hpp
