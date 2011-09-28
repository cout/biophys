#ifndef util__hpp
#define util__hpp

#include "Point.hpp"

double random_double();
Point random_onsphere(double r);
Point random_insphere(double rmin, double rmax);

#endif // util__hpp
