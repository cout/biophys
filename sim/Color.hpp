#ifndef Color__hpp
#define Color__hpp

class Color
{
public:
  Color(double r, double g, double b, double a)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
  {
  }

  double r;
  double g;
  double b;
  double a;
};

#endif // Color__hpp
