#include "CellState.h"

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
    CellState cellState;
};

//--------------------------


Cell::Cell()
{
  _x = 0;
  _y = 0;
  cellState.Set('*');
};

Cell::Cell(int x, int y, char val)
{
  _x = x;
  _y = y;
  cellState.Set(val);
};

void Cell::begin()
{
  // Initialize pins if necessary
}

char Cell::Val()
{
  return cellState.Get();
}

void Cell::SetVal(char ch)
{
  cellState.Set(ch);
}

