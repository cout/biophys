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

// http://paulbourke.net/geometry/sphereline/
bool ray_intersects_sphere(Point p1, Point p2, Point sc, double r)
{
  double a, b, c;
  double bb4ac;
  Point dp;

  dp.x = p2.x = p1.x;
  dp.y = p2.y - p1.y;
  dp.z = p2.z - p1.z;

  a = (dp.x * dp.x) + (dp.y * dp.y) + (dp.z * dp.z);
  b = 2 * (dp.x * (p1.x - sc.x) + dp.y * (p1.y - sc.y) + dp.z * (p1.z - sc.z));
  c = (sc.x * sc.x) + (sc.y * sc.y) + (sc.z * sc.z)
      + (p1.x * p1.x) + (p1.y * p1.y) + (p1.z * p1.z)
      - 2 * ((sc.x * p1.x) + (sc.y * p1.y) + (sc.z * p1.z))
      - (r * r);

  bb4ac = (b * b) - (4 * a * c);

  if (std::fabs(a) < std::numeric_limits<double>::epsilon() || bb4ac < 0)
  {
    return false;
  }

  // TODO: this condition will be reached for every particle in the
  // system.  Can we somehow avoid doing the sqrt?

  /*
  double sqrt_bb4ac = std::sqrt(bb4ac);
  double mu1 = (-b + sqrt_bb4ac) / (2 * a);
  double mu2 = (-b - sqrt_bb4ac) / (2 * a);

  if ((mu1 >= 0 && mu1 <= 1) || (mu2 >=0 && mu2 <= 1))
  {
    if (mu1 == mu2)
    {
      // line segment is tangential to the sphere
      return false;
    }
    else
    {
      // line segment intersects the sphere
      return true;
    }
  }
  else
  {
    // line segment does not intersect sphere
    return false;
  }
  */
  double u = ((sc.x-p1.x)*(p2.x-p1.x) + (sc.y-p1.y)*(p2.y-p1.y) + (sc.z-p1.z)*(p2.z-p1.z)) /
             ((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z));
  if (u >= 0 && u <= 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

