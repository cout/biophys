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

  void move_to(Point p)
  {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
  }

  double x, y, z;

private:
};

#endif // Point__hpp
