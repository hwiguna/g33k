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
    void DebugNum(char label[], int num);
    void DebugNum2(char label[], int num1, int num2);
    int Flock(int row);
};

Board::Board()
{
}

void Board::Init(char puzzle[][9])
{
  for (int x=0; x<9; x++) {
    for (int y=0; y<9; y++) {
      _cells[x][y].SetVal( puzzle[y][x] );
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
  // .. Iterate through all rows
  for (int row=0; row<9; row++)
  {
    for (int col=0; col<9; col++)
    {
      DebugNum2("Scanning row,col=", row, col);
    }
  }
}

void Board::DebugNum(char label[], int num)
{
  Serial.print(label);
  Serial.println(num);
}

void Board::DebugNum2(char label[], int num1, int num2)
{
  Serial.print(label);
  Serial.print(num1);
  Serial.print(", ");
  Serial.println(num2);
}

int Board::Flock(int row)
{
  return row / 3;
}

