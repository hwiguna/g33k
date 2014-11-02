class Scanner
{
  public:
    Scanner(Debug inDebug, Board *board);
    void Solve();
  private:
    Debug debug;
    Board *board;
    void PruneCandidates();
    void PruneByY(byte y);
    void PruneByX(byte x);
    void PruneByBox(byte x, byte y);
    void PruneCells(Cell* cells[]);
    void FindWinners();
};

Scanner::Scanner(Debug inDebug, Board *inBoard)
{
  debug = inDebug;
  board = inBoard;
}

void Scanner::Solve()
{
  PruneCandidates();
  FindWinners();
}

void Scanner::PruneCandidates()
{
  for (byte y=0; y<9; y++)
    PruneByY(y);

  for (byte x=0; x<9; x++)
    PruneByX(x);

  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++)
      PruneByBox(x,y);  
}

void Scanner::PruneByY(byte y)
{
  debug.DebugNum("Pruning row ", y);
  // Scan every column in row y
  for (byte x=0; x<9; x++)
  {
    Cell* cell = board->GetCell(x,y);
    if ( cell->IsSolved() ) 
    {
      byte val = cell->Get();
      debug.DebugNum2("At column x found a solved value of val = ", x, val);
      // Because this column has been solved, then none of the other columns in that row can be that number.
      for (byte x2=0; x2<9; x2++)
      {
        board->GetCell(x2,y)->RemoveCandidate( val );
      }
    }
  }
}

void Scanner::PruneByX(byte x)
{
  debug.DebugNum("Pruning column ", x);
  // Scan every column in row y
  for (byte y=0; y<9; y++)
  {
    Cell* cell = board->GetCell(x,y);
    if ( cell->IsSolved() ) 
    {
      byte val = cell->Get();
      debug.DebugNum2("At row y found a solved value of val = ", y, val);
      // Because this column has been solved, then none of the other columns in that row can be that number.
      for (byte y2=0; y2<9; y2++)
      {
        board->GetCell(x,y2)->RemoveCandidate( val );
      }
    }
  }
}

void Scanner::PruneByBox(byte x0, byte y0)
{
  debug.DebugNum2("Pruning box x0,y0 = ", x0,y0);
  Cell* cells[9];
  
  byte i = 0;
  x0 = x0*3;
  y0 = y0*3;
  for (byte y=0; y<3; y++)
  {
    for (byte x=0; x<3; x++)
    {
      cells[i++] = board->GetCell(x0+x,y0+y);
    }
  }
  
  PruneCells( cells );
}

void Scanner::PruneCells(Cell* cells[])
{
  debug.DebugStr("PruneCells", "");
  // Scan every column in row y
  for (byte i=0; i<9; i++)
  {
    Cell* cell = cells[i];
    if ( cell->IsSolved() ) 
    {
      byte val = cell->Get();
      debug.DebugNum2("At index i found a solved value of val = ", i, val);
      // Because this column has been solved, then none of the other columns in that row can be that number.
      for (byte j=0; j<9; j++)
      {
        cells[j]->RemoveCandidate( val );
      }
    }
  }
}


//------------------------

void Scanner::FindWinners()
{
  // .. Iterate through all rows and columns
  for (byte y=0; y<9; y++)
  {
    for (byte x=0; x<9; x++)
    {
      //debug.DebugNum2("Finding Winners x,y=", x, y);
      // If not solved, prune against numbers on that row
      board->GetCell(x,y)->FindWinner();
    }
  }
}


