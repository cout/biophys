#ifndef util__hpp
#define util__hpp

#include "Point.hpp"

double random_double();
Point random_onsphere(double r);
Point random_insphere(double rmin, double rmax);
bool ray_intersects_sphere(Point p1, Point p2, Point sc, double r);

#endif // util__hpp
