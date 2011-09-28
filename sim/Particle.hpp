#ifndef Particle__hpp
#define Particle__hpp

class Particle
{
public:
  Particle()
    : x(0)
    , y(0)
    , z(0)
  {
  }

  double x, y, z;

  void random_walk(double max);

private:
};

#endif // Particle__hpp
