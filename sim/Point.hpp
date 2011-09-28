#ifndef Point__hpp
#define Point__hpp

class Point
{
public:
  Point(double x = 0, double y = 0, double z = 0)
    : x(x)
    , y(y)
    , z(z)
  {
  }

  double x, y, z;

private:
};

#endif // Point__hpp
