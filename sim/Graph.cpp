#include "Graph.hpp"

#include <GL/gl.h>

Graph::
Graph()
  : values_()
{
}

void
Graph::
add_point(double t, double val)
{
  values_.push_back(std::make_pair(t, val));
}

void
Graph::
draw()
{
  auto it(values_.begin());
  auto end(values_.end());

  glPointSize(1.0);
  glBegin(GL_POINTS);
  for(; it != end; ++it)
  {
    glVertex3d(it->first, it->second, 0);
  }
  glEnd();
}

