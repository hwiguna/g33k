const byte SOLVED_BIT = 11;

class Cell
{
  public:
    Cell();
    void SetDebug(Debug inDebug);
    void Set(byte num);
    byte Get();
    unsigned int GetBits();
    void AddCandidate(byte num);
    void RemoveCandidate(byte num);
    boolean IsSolved();
    void Solved();
    boolean Maybe(byte num);
    boolean FindWinner();
  private:
    unsigned int _vals;
    Debug debug;
};

Cell::Cell()
{
};

void Cell::SetDebug(Debug inDebug)
{
  debug = inDebug;
}


void Cell::Set(byte num)
{
  // Status of each cell is stored as bits in _vals
  // bit 0: Least Significant bit represents a blank (unknown)
  // bit 1..9: represents digits 1..9.  If a cell is not yet solved, multiple on bits represent possible values for the cell.
  // bit 10: skipped to make bit 11 stand out from the rest of the lower bits.
  // bit 11: 1 means this cell is solved, 0 means we don't know for sure (even if only one of bits 1..9 is on.
  //S 98 7654 3210      
  //0011 1111 1111
  //3    F    F

  if (num==0)
  {
    _vals = 0x03FF; //Not solved and 9 lowest bits on meaning all # are possible candidates
  }
  else
  {
    _vals = 0;
    bitSet(_vals, num);
    Solved();
  }
}

unsigned int Cell::GetBits()
{
  return _vals;
}

byte Cell::Get()
{
  byte num = 0;
  if (IsSolved())
  {
    for (byte i=1; i<=9; i++)
    {
      if (bitRead(_vals,i)) {
        num = i;
        break;
      }
    }
  }
  return num;
}

void Cell::AddCandidate(byte num)
{
  if (!IsSolved())
    bitSet(_vals, num);
}

void Cell::RemoveCandidate(byte num)
{
  if (!IsSolved()) {
    bitClear(_vals, num);
  }
}

boolean Cell::IsSolved()
{
  return bitRead(_vals, SOLVED_BIT) != 0;
}

void Cell::Solved()
{
  bitSet(_vals,SOLVED_BIT);
}

boolean Cell::Maybe(byte num)
{
  return bitRead( _vals, num) == 0;
}

boolean Cell::FindWinner()
{
  boolean found = false;
  
  if (!IsSolved())
  {
    byte candidateCount = 0;
    for (byte i=1; i<=9; i++)
    {
      //debug.DebugNum2("i,bitval ",i,bitRead(_vals,i));
      if (bitRead(_vals,i)==1)
        candidateCount++;
    }
    
    if (candidateCount==1) {
      Solved();
      debug.DebugNum("*** Found winner *** val=", Get());
      found = true;
    }
  }
  
  return found;
}

