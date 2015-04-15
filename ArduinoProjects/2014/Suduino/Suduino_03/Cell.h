#include "Arduino.h"
#include "List.h"

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
    List candidates;
    //List rejects;
};

//--------------------------


Cell::Cell()
{
  _x = 0;
  _y = 0;
  candidates.Add('*');
};

Cell::Cell(int x, int y, char val)
{
  _x = x;
  _y = y;
  candidates.Add(val);
};

void Cell::begin()
{
  // Initialize pins if necessary
}

char Cell::Val()
{
  return candidates.First();
}

void Cell::SetVal(char ch)
{
  candidates.Add(ch);
}

