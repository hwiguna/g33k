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
    
    boolean AreValid();
    boolean IsValid(Cell* cells[]);

    boolean Election();
    boolean FindDuplicate(byte x, byte y, Cell* cell, byte num, Cell* cells[]);
};

Scanner::Scanner(Debug inDebug, Board *inBoard)
{
  debug = inDebug;
  board = inBoard;
}

void Scanner::Solve()
{
  boolean found1 = true;
  boolean found2 = true;
  boolean found3 = true;
  boolean found4 = true;
  while (found1 || found2 || found3)
  {
    PruneCandidates();      AreValid();
    found1 = FindWinners(); AreValid();
    Deduce();               AreValid();   
    found2 = FindWinners(); AreValid();
    found3 = Election();
    
    //success2 = ElectSingles();
    debug.DebugNum2("Solve status: found1,found2 = ", found1,found2);
    debug.DebugNum2("found3,found4 = ", found3,found4);
  }
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
      if (x==2 && y==2) {
        board->Print2();
      }
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
  //debug.DebugNum("GetYCells y=", y);
  for (byte x=0; x<9; x++)
    cells[x] = board->GetCell(x,y);
}

void Scanner::GetXCells(byte x, Cell* cells[])
{
  //debug.DebugNum("GetXCells x=", x);
  for (byte y=0; y<9; y++)
    cells[y] = board->GetCell(x,y);
}

void Scanner::GetBoxCells(byte x0, byte y0, Cell* cells[])
{
  //debug.DebugNum2("GetBoxCells x0,y0 = ", x0,y0);
  byte i = 0;
  x0 = x0*3;
  y0 = y0*3;
  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++)
      cells[i++] = board->GetCell(x0+x,y0+y);
}

void Scanner::PruneCells(Cell* cells[])
{
  //debug.DebugStr("PruneCells", "");
  for (byte i=0; i<9; i++)
  {
    Cell* cell = cells[i];
    if ( cell->IsSolved() ) 
    {
      byte val = cell->Get();
      //debug.DebugNum2("At index i found a solved value of val = ", i, val);
      // Because this column has been solved, then none of the other columns in that row can be that number.
      //board->Print2();
      for (byte j=0; j<9; j++)
      {
        cells[j]->RemoveCandidate( val );
        AreValid();
      }
      //board->Print2();
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
        AreValid();
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
      // If not solved, prune against numbers on that row
      if (board->GetCell(x,y)->FindWinner()) {
        debug.DebugNum2("Found Winner at x,y=", x, y);        
        found = true;
        AreValid();
      }
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
      board->Print2();
      cells[ candidateIndex ]->Set(num);
      board->Print2();
    }
  }
}

boolean Scanner::AreValid()
{
  boolean isValid = true;
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    if (!IsValid( cells )) isValid=false;
  }

  if (isValid)
    for (byte x=0; x<9; x++) {
      GetXCells(x, cells);
      if (!IsValid( cells )) isValid=false;
    }

  if (isValid)
    for (byte y=0; y<3; y++)
      for (byte x=0; x<3; x++) {
        GetBoxCells(x,y, cells); 
        if (!IsValid( cells )) isValid=false;
      }

  return isValid;
}

boolean Scanner::IsValid(Cell* cells[])
{
  boolean isValid = true;

  for (byte cellIndex=0; cellIndex<(9-1); cellIndex++)
  {
    Cell* cell = cells[cellIndex];
    if ( cell->IsSolved() ) 
    {
      byte cellVal = cell->Get();
      
      for (byte chkIndex=cellIndex+1; chkIndex<9; chkIndex++)
      {
         if ( cells[chkIndex]->IsSolved() ) 
         {
            byte chkVal = cells[chkIndex]->Get();
            if (cellVal == chkVal) {
              isValid = false;
              debug.DebugStr("*** B A D *** B A D *** B A D ******************************","");
              board->Print2();
              chkIndex = 9;
              cellIndex = 9;
            }
         }
      }
    }
  }

  return isValid;
}

boolean Scanner::Election()
{
  boolean elected = false;
  
  // Scan all cells "C"
  for (byte y=0; y<9; y++)
  {
    for (byte x=0; x<9; x++)
    {
      // if unsolved
      Cell* cell = board->GetCell(x,y);
      if (! (cell->IsSolved()) )
      {
          // For each possible num...
          for (byte num=1; num<=9; num++)
          {
            // GetY, getX, GetBox for cell "C"
            // if "num" is not found in cells of any of the GetX, GetY, or GetBox
            // then "C" is solved!
          
            Cell* cells[9];
            GetXCells(x, cells);      
            boolean foundInCol = FindDuplicate(x,0, cell, num, cells);
            
            if (!foundInCol) {
              GetYCells(y, cells);
              boolean foundInRow = FindDuplicate(0,y, cell, num, cells);
  
              if (!foundInRow) {
                GetBoxCells(x,y, cells);
                boolean foundInBox = FindDuplicate(x,y, cell, num, cells);
                
                if (!foundInBox) {
                  elected = true;
                  debug.DebugNum2("Election SUCCESS! x,y = ",x,y);
                  debug.DebugNum("num =",num);
                  board->Print2();
                  cell->Set(num);
                  AreValid();
                  break;
                }
              }
            }
          }
      }
    }
  }
  
  return elected;
}

// Find potential num in cells, exclude original cell
boolean Scanner::FindDuplicate(byte x, byte y, Cell* cell, byte num, Cell* cells[])
{
  boolean found = false;
  boolean verbose = x==5 && y==5;
  
  if (verbose) debug.DebugNum2("FindDuplicate for x,y = ", x,y);
  if (verbose) board->Print2();

  for (byte i=0; i<9; i++)
  {
    Cell* chkCell = cells[i];
    if (chkCell != cell) {
      if (verbose) debug.DebugNum("At index i. it is NOT same cell ", i);
      if ( bitRead(chkCell->GetBits(), num) == 1 ) {
        if (verbose) debug.DebugNum2("Found num at index i ", num,i);
        found = true;
        break;
      }
    }
  }
  
  if (verbose) debug.DebugNum("FindDuplicate ending with found = ", found);
  return found;
}
