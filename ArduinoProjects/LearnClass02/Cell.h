#include "Arduino.h"

class Cell
{
  public:
    Cell();
    Cell(int x, int y, char val);
    void begin();
    char Val();
    void SetVal(char ch);
  private:
    int _x;
    int _y;
    char _vals[9];
};

//--------------------------


Cell::Cell()
{
  _x = 0;
  _y = 0;
  _vals[0] = '*';
};

Cell::Cell(int x, int y, char val)
{
  _x = x;
  _y = y;
  _vals[0] = val;
};

void Cell::begin()
{
  // Initialize pins if necessary
}

char Cell::Val()
{
  return _vals[0];  
}

void Cell::SetVal(char ch)
{
  _vals[0] = ch;
}

