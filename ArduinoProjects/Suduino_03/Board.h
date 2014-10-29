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

    //List _knownVals;
    //List GetKnownNumbersByRow(int row);
    List GetKnownNumbersByRow(int row);
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
    DebugNum("Scanning row ", row);
    
    // ?? Find Known Numbers within row
    List knownVals = GetKnownNumbersByRow(row);

    // .. Iterate through known numbers
    //for (int knownIndex=0; knownIndex<knownVals.Length(); knownIndex++)
    {
      // .. Iterate through rows within current rowFlock
      int flock = Flock(row);
      DebugNum("Flock = ", flock);
      
      for (int row=0; row<9; row++)
      {
        // ?? Look for that number in row
        
        // If NOT found
          // .. Iterate through unknown columns on that row
            // If number is possible at that location, mark it as such in the cell
          // If there is only one possibility, then mark it as known
      }
    }
  }
}


List Board::GetKnownNumbersByRow(int row)
{
  List knownVals;
  
  for (int col=0; col<9; col++)
  {
    if ( _cells[col][row].Val() != '*')
      knownVals.Add( col );
  }
  
  return knownVals;
}

void Board::DebugNum(char label[], int num)
{
  Serial.print(label);
  Serial.println(num);
}

int Board::Flock(int row)
{
  return row / 3;
}

