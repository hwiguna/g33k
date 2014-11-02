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
  // .. Iterate through all rows and columns
  for (byte y=0; y<9; y++)
  {
    PruneByY(y);
  }
}

void Scanner::PruneByY(byte y)
{
  debug.DebugNum("Pruning row ", y);
  // Scan every column in row y
  for (byte x=0; x<9; x++)
  {
    Cell cell = board->GetCell(x,y);
    if ( cell.IsSolved() ) 
    {
      byte val = cell.Get();
      debug.DebugNum2("x,val = ", x, val);
      // If that column has been solved, then none of the other columns in that row can be that number.
      for (byte x2=0; x2<9; x2++)
      {
        if (y==3) debug.DebugNum2("Pruning value from column = ", val, x2);
        board->GetCell(x2,y).RemoveCandidate( val );
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
      debug.DebugNum2("Finding Winners x,y=", x, y);
      // If not solved, prune against numbers on that row
      board->GetCell(x,y).FindWinner();
    }
  }
}


