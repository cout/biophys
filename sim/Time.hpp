#ifndef Time__hpp
#define Time__hpp

#include <sys/time.h>

class Time
{
public:
  Time()
    : d_(0)
  {
  }

  Time(double d)
    : d_(d)
  {
  }

  Time(struct timeval const & tv)
    : d_(tv.tv_sec + tv.tv_usec / 1000000.0)
  {
  }

  operator double() const { return d_; }

  static Time now() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return Time(tv);
  }

private:
  double d_;
};

#endif // Time__hpp

