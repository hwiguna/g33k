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
    void Deduce1Missing(Cell* cells[]);
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
     
  //Deduce1Missing( cells );
}

void Scanner::PruneByY(byte y)
{
  debug.DebugNum("Pruning row ", y);
  Cell* cells[9];
  for (byte x=0; x<9; x++)
    cells[x] = board->GetCell(x,y);

  PruneCells( cells );
}

void Scanner::PruneByX(byte x)
{
  debug.DebugNum("Pruning column ", x);
  Cell* cells[9];
  for (byte y=0; y<9; y++)
    cells[y] = board->GetCell(x,y);

  PruneCells( cells );
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

void Scanner::Deduce1Missing(Cell* cells[])
{
  debug.DebugStr("Deduce1Missing", "");
  byte missingCount = 9;
  byte missingNum = 0;
  for (byte i=0; i<9; i++)
  {
    if (cells[i]->IsSolved())
      missingCount--;
    else
      missingNum = cells[i]->Get();
  }
  if (missingCount == 1)
  {
    debug.DebugNum("It's missing a ", missingNum);
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


