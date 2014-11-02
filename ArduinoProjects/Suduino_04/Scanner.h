class Scanner
{
  public:
    Scanner(Debug inDebug, Board *board);
    void Solve();
  private:
    Debug debug;
    Board *board;

    void GetYCells(byte y, Cell* cells[]);
    void GetXCells(byte x, Cell* cells[]);
    void GetBoxCells(byte x, byte y, Cell* cells[]);

    void PruneCandidates();
    void PruneCells(Cell* cells[]);

    boolean Deduce();
    boolean Deduce1Missing(Cell* cells[]);

    boolean ElectSingles();
    boolean ElectSingleCandidates(Cell* cells[]);

    boolean FindWinners();
};

Scanner::Scanner(Debug inDebug, Board *inBoard)
{
  debug = inDebug;
  board = inBoard;
}

void Scanner::Solve()
{
  boolean found = true;
  boolean success = true;
  boolean success2 = true;
  while (found || success)
  {
    PruneCandidates();
    found = FindWinners();
    success = Deduce();
    success2 = ElectSingles();
    debug.DebugNum2("Solve status: found,success = ", found,success);
  }
  board->Print2();
}

boolean Scanner::Deduce()
{
  boolean success = false;
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    if (Deduce1Missing( cells )) success = true;
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    if (Deduce1Missing( cells )) success = true;
  }

  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      if (Deduce1Missing( cells )) success = true;
    }
  return success;
}

void Scanner::PruneCandidates()
{
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    PruneCells(cells);
    //board->Print2();
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    PruneCells(cells);
    //board->Print2();
  }
  
  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      PruneCells(cells);
      //board->Print2();
    }
}


boolean Scanner::ElectSingles()
{
  boolean success = false;
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    if (ElectSingleCandidates( cells )) success = true;
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    if (ElectSingleCandidates( cells )) success = true;
  }

  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      if (ElectSingleCandidates( cells )) success = true;
    }
  return success;
}


void Scanner::GetYCells(byte y, Cell* cells[])
{
  debug.DebugNum("GetYCells y=", y);
  for (byte x=0; x<9; x++)
    cells[x] = board->GetCell(x,y);
}

void Scanner::GetXCells(byte x, Cell* cells[])
{
  debug.DebugNum("GetXCells x=", x);
  for (byte y=0; y<9; y++)
    cells[y] = board->GetCell(x,y);
}

void Scanner::GetBoxCells(byte x0, byte y0, Cell* cells[])
{
  debug.DebugNum2("GetBoxCells x0,y0 = ", x0,y0);
  byte i = 0;
  x0 = x0*3;
  y0 = y0*3;
  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++)
      cells[i++] = board->GetCell(x0+x,y0+y);
}

void Scanner::PruneCells(Cell* cells[])
{
  debug.DebugStr("PruneCells", "");
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

boolean Scanner::Deduce1Missing(Cell* cells[])
{
  //debug.DebugStr("Deduce1Missing", "");
  unsigned int foundFlags;
  boolean success = false;
  byte foundCount = 0;
  byte deducedIndex = 0;
  for (byte i=0; i<9; i++)
  {
    if (cells[i]->IsSolved()) {
      bitSet(foundFlags, cells[i]->Get());
      foundCount++;
    }
    else
      deducedIndex = i;
  }

  if (foundCount == 8)
  {
    for (byte num=1; num<=9; num++)
    {
      if (bitRead(foundFlags,num)==0) {
        debug.DebugNum("Deduce1Missing deduced that this is the missing num ", num);
        cells[ deducedIndex ]->Set(num);
        success = true;
      }
    }
  }
  
  return success;
}

//------------------------

boolean Scanner::FindWinners()
{
  boolean found = false;
  
  // .. Iterate through all rows and columns
  for (byte y=0; y<9; y++)
  {
    for (byte x=0; x<9; x++)
    {
      //debug.DebugNum2("Finding Winners x,y=", x, y);
      // If not solved, prune against numbers on that row
      if (board->GetCell(x,y)->FindWinner())
        found = true;
      //board->Print2();
    }
  }
  
  return found;
}

boolean Scanner::ElectSingleCandidates(Cell* cells[])
{
  debug.DebugStr("ElectSingleCandidates", "");
  boolean success = false;
  for (byte num=1; num<=9; num++)
  {
    byte candidateCount = 0;
    byte candidateIndex = 0;
    for (byte i=0; i<9; i++)
    {
      if (!cells[i]->IsSolved()) {
        unsigned int foundFlags = cells[i]->GetBits();
        if (bitRead(foundFlags,num)) {
          candidateCount++;
          candidateIndex = i;
        }
      }
    }
    
    if (candidateCount==1) {
      debug.DebugNum2("*** ElectSingleCandidates success *** index,num = ", candidateIndex, num);
      success = true;
      cells[ candidateIndex ]->Set(num);
    }
  }
}



