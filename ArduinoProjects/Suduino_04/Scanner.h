const boolean ASSERT = false;

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

    boolean FindWinners();

    boolean FindMissingDigits();
    boolean FindMissingDigit(Cell* cells[]);
    
    boolean FindOnlyOptions();
    boolean FindDuplicate(byte x, byte y, Cell* cell, byte num, Cell* cells[]);

    boolean FindClumps();
    boolean FindClump(Cell* cells[]);
    byte PatternLength( unsigned int pattern);

    boolean AreValid();
    boolean IsValid(Cell* cells[]);
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
  while (found1 || found2 || found3 | found4)
  {
    PruneCandidates();      AreValid();
    found1 = FindWinners(); AreValid();
    FindMissingDigits();    AreValid();   
    found2 = FindWinners(); AreValid();
    found3 = FindOnlyOptions(); AreValid();
    found4 = FindClumps();   AreValid();
    
    //success2 = ElectSingles();
    debug.DebugNum2("Solve status: found1,found2 = ", found1,found2);
    debug.DebugNum2("found3,found4 = ", found3,found4);
  }
}

boolean Scanner::FindMissingDigits()
{
  boolean success = false;
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    if (FindMissingDigit( cells )) success = true;
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    if (FindMissingDigit( cells )) success = true;
  }

  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      if (FindMissingDigit( cells )) success = true;
    }
  return success;
}

void Scanner::PruneCandidates()
{
  Cell* cells[9];

  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    PruneCells(cells);
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    PruneCells(cells);
  }
  
  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      PruneCells(cells);
    }
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
    }
  }
}

boolean Scanner::FindMissingDigit(Cell* cells[])
{
  //debug.DebugStr("FindMissingDigit", "");
  unsigned int foundFlags;
  boolean success = false;
  byte foundCount = 0;
  byte deducedIndex = 0;
  
  // Walk through a given 9 cells. Count how many of them have been solved.
  for (byte i=0; i<9; i++)
  {
    if (cells[i]->IsSolved()) {
      bitSet(foundFlags, cells[i]->Get()); // Keep track of the solved numbers.
      foundCount++;
    }
    else
      deducedIndex = i; // Index of the unsolved cell.  Value is only valid and used if only one cell is unsolved.
  }

  // If all but one has been solved, then we can figure out which number is missing!
  if (foundCount == 8)
  {
    // Go through all 9 numbers...
    for (byte num=1; num<=9; num++)
    {
      // Find the one missing unsolved number that were not marked above.
      if (bitRead(foundFlags,num)==0) {
        debug.DebugNum("FindMissingDigits deduced that this is the missing num ", num);
        cells[ deducedIndex ]->Set(num); // Mark this cell as solved!
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

boolean Scanner::AreValid()
{
  boolean isValid = true;

  if (ASSERT)
  {
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

boolean Scanner::FindOnlyOptions()
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
                // Translate actual x,y to box coordinates (0..3,0..3)
                int bx = x / 3;
                int by = y / 3;
                GetBoxCells(bx,by, cells);
                boolean foundInBox = FindDuplicate(x,y, cell, num, cells);
                
                if (!foundInBox) {
                  elected = true;
                  debug.DebugNum2("FindOnlyOptions SUCCESS! x,y = ",x,y);
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

boolean Scanner::FindClumps()
{
  boolean found = false;
  board->Print2();

 Cell* cells[9];
  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    debug.DebugNum("\nFindClump for Y = ", y);
    if (FindClump(cells)) found = true;
  }
  
  return found;
}

boolean Scanner::FindClump(Cell* cells[])
{
  boolean found = false;
  debug.DebugStr("FindClump()","");
  
  unsigned int patterns[9]; // What's the bit pattern look like?
  byte numPatterns = 0; // How many unique bit patterns were there?
  byte patternLen[9]; // How long is this bit pattern
  byte patternCount[9]; // How many did this particular bit pattern occured within cells?

  //-- Loop thru the cells, counting the unsolved patterns --
  for (byte i=0; i<9; i++)
  {
    Cell* chkCell = cells[i];
    
    // Only count unsolved patterns
    if (!chkCell->IsSolved()) {
      // Mask out other bits except the flags that indicates possible numbers for the cell
      unsigned int pattern = chkCell->GetBits() & 0x03FE;
      debug.DebugNum2("Unsolved at index, pattern = ",i, pattern);
      // Is this pattern in the patterns array?
      boolean patternFound = false;
      for (byte c=0; c<numPatterns; c++)
      {
        if (pattern == patterns[c])
        {
          // existing found, increment count for that pattern
          patternFound = true;
          patternCount[c]++;
          debug.DebugNum2("Found existing: i, count = ", i, patternCount[c]);
          break;
        }
      }
      
      if (!numPatterns) {
        patterns[numPatterns] = pattern;
        patternLen[numPatterns] = PatternLength(pattern);
        patternCount[numPatterns] = 1;
        debug.DebugNum2("Added new: i, pattern = ", i, pattern);
        numPatterns++;
      }
    }
  }
  
  //-- Any of the patterns have count greater than one? --
  
}


byte Scanner::PatternLength( unsigned int pattern)
{
  byte patternLen = 0;
  for (byte b=1; b <= 9; b++)
  {
    if (bitRead(pattern,b)>0)
      patternLen++;
  }
  
  debug.DebugNum("PatternLength = ", patternLen);
  return patternLen;
}
