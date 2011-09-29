#include "util.hpp"

#include <cmath>
#include <cstdlib>
#include <limits>

double random_double()
{
  return double(std::rand()) / RAND_MAX;
}

// http://permalink.gmane.org/gmane.games.devel.algorithms/19227
Point random_onsphere(double r)
{
  double theta = M_PI * 2 * random_double();
  double phi = std::acos(1.0 - 2 * random_double());

  double sp = std::sin(phi) * r;
  double x = std::cos(theta) * sp * r;
  double y = std::sin(theta) * sp * r;
  double z = std::cos(phi);

  Point p(x, y, z);
  return p;
}

// http://en.wikipedia.org/wiki/N-sphere#Generating_random_points
Point random_insphere(double rmin, double rmax)
{
  Point p = random_onsphere(1.0);

  double u = std::pow(random_double(), 1.0/3.0);
  double r = (rmax - rmin) * u + rmin;

  p.x *= r;
  p.y *= r;
  p.z *= r;

  return p;
}

// thanks, eiffel :)
bool is_inside_sphere(Point p, Point sc, double r)
{
  p.x -= sc.x;
  p.y -= sc.y;
  p.z -= sc.z;

  return p.x*p.x + p.y*p.y + p.z*p.z < r*r;
}

bool ray_intersects_sphere(Point p1, Point p2, Point sc, double r)
{
  bool p1_inside = is_inside_sphere(p1, sc, r);
  bool p2_inside = is_inside_sphere(p2, sc, r);

  return (p1_inside != p2_inside);
}

