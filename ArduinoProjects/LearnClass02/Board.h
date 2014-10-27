#include "Cell.h"

class Board
{
  public:
    Board();
    void Init(char puzzle[][9]);
    Cell GetCell(int x, int y);
    void SetCell(int x, int y, char ch);
    void Print();
    void Solve();
  private:
    Cell _cells[9][9];
};

Board::Board()
{
}

void Board::Init(char puzzle[][9])
{
  for (int x=0; x<9; x++) {
    for (int y=0; y<9; y++) {
      _cells[x][y].SetVal( puzzle[x][y] );
    }
  }
}

Cell Board::GetCell(int x, int y)
{
  return _cells[x][y];
}


void Board::SetCell(int x, int y, char ch)
{
  _cells[x][y].SetVal(ch);
}

void Board::Print()
{
  for (int y=0; y<9; y++) {
    for (int x=0; x<9; x++) {
      Serial.print( " " );
      Serial.print( _cells[x][y].Val() );
      if (x==2 || x==5) Serial.print( "  " );
    }
    Serial.println();
    if (y==2 || y==5) Serial.println();
  }
}

void Board::Solve()
{
  
}
