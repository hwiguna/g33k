const boolean ASSERT = true;

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
    Cell* FindUnsolvedCell( Cell* cells[], byte startIndex, byte endIndex);

    //-- Eliminate solved from candidates --
    void PruneCandidates();
    void PruneCells(Cell* cells[]);

    //-- Mark cells with only one candidate as solved --
    boolean FindWinners();
    boolean FindUniqueCandidates();
    
    //-- Look at rows, cells, boxes, for last unsolved number --
    boolean FindMissingDigits();
    boolean FindMissingDigit(Cell* cells[]);
    
    //-- If a number is not in that cell's row/col/box, then that cell MUST contain that number --
    boolean FindOnlyOptions();
    boolean FindDuplicate(byte x, byte y, Cell* cell, byte num, Cell* cells[]);

    //-- Use cells with identical candidates, to prune the last candidate --
    boolean FindClumps();
    boolean FindClump(Cell* cells[]);
    //byte PatternLength( unsigned int pattern);

    //-- Use groups of three rows/columns to deduce the location of the missing number --
    boolean FindInFlocks();
    boolean FindInFlock(Cell* cellz[][9]);

    //-- Validate that all solved numbers so far do not violate the sudoku rules --
    boolean AreValid();
    boolean IsValid(Cell* cells[]); // Prints BAD if cells contain duplicate numbers
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
  boolean found5 = true;
  boolean found6 = true;
  while (found1 || found2 || found3 || found4 || found5)
  {
    PruneCandidates();      AreValid();
    found1 = FindWinners(); AreValid();
    found2 = FindUniqueCandidates(); AreValid();
    FindMissingDigits();    AreValid();   
    found3 = FindWinners(); AreValid();
    found4 = FindOnlyOptions(); AreValid();
    found5 = FindClumps();  AreValid();
    found6 = FindInFlocks();AreValid();

    //success2 = ElectSingles();
    debug.DebugNum2("Solve status: found1,found2 = ", found1,found2);
    debug.DebugNum2("found3,found4 = ", found3,found4);
    debug.DebugNum2("found5, found6 = ", found5, found6);
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

boolean Scanner::FindUniqueCandidates()
{
  boolean found = false;
  
  // .. Iterate through all rows and columns
  for (byte y=0; y<9; y++)
  {
    for (byte x=0; x<9; x++)
    {
      Cell* cell = board->GetCell(x,y);

      // Go through all numbers, looking for candidate that only has one option within a box
      for (byte num=1; num<=9; num++)
      {
        int bx = x / 3;
        int by = y / 3;
        Cell* cells[9];
        GetBoxCells(bx,by, cells);
        boolean foundInBox = FindDuplicate(x,y, cell, num, cells);
        
        if (!foundInBox) {
          found = true;
          debug.DebugNum2("FindUniqueCandidates SUCCESS! x,y = ",x,y);
          debug.DebugNum("num =",num);
          board->Print2();
          cell->Set(num);
          AreValid();
          break;
        }
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
  //board->Print2();

  Cell* cells[9];
  for (byte y=0; y<9; y++) {
    GetYCells(y, cells);
    //debug.DebugNum("\nFindClump for Y = ", y);
    if (FindClump(cells)) found = true;
  }

  for (byte x=0; x<9; x++) {
    GetXCells(x, cells);
    //debug.DebugNum("\nFindClump for X = ", x);
    if (FindClump( cells )) found = true;
  }

  for (byte y=0; y<3; y++)
    for (byte x=0; x<3; x++) {
      GetBoxCells(x,y, cells); 
      //debug.DebugNum2("\nFindClump for x,y = ", x,y);
      if (FindClump( cells )) found = true;
    }
  
  return found;
}

boolean Scanner::FindClump(Cell* cells[])
{
  boolean found = false;
  //debug.DebugStr("FindClump()","");

  Pattern pattern;
  PatternList patternList = PatternList(debug);
  byte unsolvedCount = 0;
  unsigned int missingNum = 0x3FE;
  
  //-- Loop thru the cells, counting the unsolved patterns --
  for (byte i=0; i<9; i++)
  {
    Cell* chkCell = cells[i];
    
    if (chkCell->IsSolved()) {
      // Mark solved numbers as NOT missing
      byte val = chkCell->Get();
      debug.DebugNum("Found solved val = ", val);
      bitClear(missingNum,val);
    }
    else
    {
      unsolvedCount++;  // Count unsolved patterns
      pattern.Set(chkCell->GetBits() & 0x03FE); // 0x03FE masks out other bits except the flags that indicates possible numbers for the cell
      debug.DebugNum2("Unsolved at index, pattern = ",i, pattern.Get());
      boolean patternFound = patternList.CollectPattern(pattern);// Is this pattern in the patterns array?
    }
  }

  //-- Any of the patterns have count greater than one? --
  byte numPatterns = patternList.NumPatterns();
  debug.DebugNum("Step 2: numPatterns = ", numPatterns);
  for (byte p=0; p<numPatterns; p++)
  {
    Pattern* pattern = patternList.Get(p);
    byte patternCount = pattern->GetCount();
    byte patternLength = pattern->Length();
    debug.DebugNum2("patternCount, patternLen = ", patternCount, patternLength);
    if ( (patternCount == patternLength) && ((patternCount+1) == unsolvedCount) )
    {
      debug.DebugNum2("patternCount, unsolvedCount = ", patternCount, unsolvedCount);

      unsigned int patternInt = pattern->Get();
      debug.DebugNum2("*** p, pattern = ", p, patternInt);

      // mark the two nums as "taken" so we can find the missing num
      for (byte b=1; b<=9; b++)
      {
        if (bitRead(patternInt,b) != 0)
        {
          debug.DebugNum("Marking b as taken ", b);
          bitClear(missingNum,b);
        }
      }
      
      //-- We now know the pattern that appears twice in the cells AND we know that there is only one more unknown
      // Prune the remaining unsolved cells with bits in pattern
      for (byte c=0; c<9; c++)
      {
        // find the lone unsolved that has a different pattern than the double.
        if (!cells[c]->IsSolved() && (cells[c]->GetBits() & 0x3FE) != patternInt)
        {
          // Translate missingNum bit into actual num
          byte val = 0;
          for (byte b=1; b<=9; b++)
          {
            if (bitRead(missingNum,b))
              val = b;
          }
          debug.DebugNum2("cell c solved as val = ", c, val);
          cells[c]->Set(val);
          found = true;
        }
      }
    }
  }

  return found;
}


boolean Scanner::FindInFlocks()
{
  boolean found = false;
  board->Print2();

  Cell* cellz[3][9];

  for (byte x0=0; x0<3; x0++) 
  {
    byte x = x0*3;
    GetXCells(x, cellz[0]);
    GetXCells(x+1, cellz[1]);
    GetXCells(x+2, cellz[2]);
    debug.DebugNum("\nFindFlock for X = ", x);
    if (FindInFlock(cellz)) found = true;
  }

  for (byte y0=0; y0<3; y0++) 
  {
    byte y = y0*3;
    GetYCells(y, cellz[0]);
    GetYCells(y+1, cellz[1]);
    GetYCells(y+2, cellz[2]);
    debug.DebugNum("\nFindFlock for Y = ", y);
    if (FindInFlock(cellz)) found = true;
  }

  return found; 
}

boolean Scanner::FindInFlock(Cell* cellz[][9])
{
  boolean found = false;

  for (byte digit=1; digit<=9; digit++)
  {
    debug.DebugNum("Finding digit = ", digit);
    byte foundCount = 0;
    boolean inFlock[3] = {0,0,0};
    boolean inBox[3] = {0,0,0};
    
    for (byte flockIndex=0; flockIndex<3; flockIndex++)
    {
      for (byte cellIndex=0; cellIndex<9; cellIndex++)
      {
        Cell* cell = cellz[flockIndex][cellIndex];
        if ( cell->Get()==digit && cell->IsSolved() )
        {
          foundCount++;
          debug.DebugNum2("found digit at flockIndex, cellIndex = ", flockIndex, cellIndex);
          inFlock[flockIndex] = true;
          inBox[ cellIndex/3 ] = true;
        }
      }
    }
      
    if (foundCount==2) {
      byte flock;
      byte box;
      for (byte i=0; i<3; i++)
      {
        if (!inFlock[i]) flock=i;
        if (!inBox[i]) box=i;
      }
      debug.DebugNum2("Narrowed down to flock,box = ", flock, box);
      
      Cell* cell = FindUnsolvedCell( cellz[flock], box*3, box*3+3 );
      if (cell != NULL)
      {
        debug.DebugNum("*** *** Solved digit = ", digit);
        cell->Set(digit);
      }
    }
  }
  return found; 
}

Cell* Scanner::FindUnsolvedCell( Cell* cells[], byte startIndex, byte endIndex)
{
  Cell* foundCell;
  byte foundCount = 0;
  
  for (byte cellIndex=startIndex; cellIndex<endIndex; cellIndex++)
  {
    if (! cells[cellIndex]->IsSolved())
    {
      foundCount++;
      foundCell = cells[cellIndex];
      debug.DebugNum2("FindUnsolvedCell. cellIndex, foundCount = ", cellIndex, foundCount);
    }
  }
  
  if (foundCount!=1) 
  {
    foundCell = NULL;
  }
  
  return foundCell;
}

