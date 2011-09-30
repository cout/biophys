#ifndef Na_K_Pump__hpp
#define Na_K_Pump__hpp

class Ions;
class Cell;

class Na_K_Pump
{
public:
  Na_K_Pump();

  void pump(
      Ions & sodium,
      Ions & potassium,
      Cell const & cell);

private:
};

#endif // Na_K_Pump__hpp
