#include "CellState.h"

class Cell
{
  public:
    Cell();
    Cell(byte x, byte y, byte val);
    void begin();
    byte Val();
    boolean IsSolved();
    void SetVal(byte num);
    void RemoveCandidate(byte num);
    void FindWinner();
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

Cell::Cell(byte x, byte y, byte num)
{
  _x = x;
  _y = y;
  cellState.Set(num);
};

void Cell::begin()
{
  // Initialize pins if necessary
}

byte Cell::Val()
{
  return cellState.Get();
}

void Cell::SetVal(byte num)
{
  cellState.Set(num);
}

boolean Cell::IsSolved()
{
  return cellState.IsSolved();
}

void Cell::RemoveCandidate(byte num)
{
  cellState.RemoveCandidate(num);
}

void Cell::FindWinner()
{
  cellState.FindWinner();
}

