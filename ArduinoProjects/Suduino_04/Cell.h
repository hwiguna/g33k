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
    boolean UnitTests();
    boolean FindWinner();
  private:
    unsigned int _vals;
    Debug debug;
};

//--------------------------


Cell::Cell()
{
  //Set(0);
};

void Cell::SetDebug(Debug inDebug)
{
  debug = inDebug;
  // Initialize pins if necessary
}

//-----------------------------
//S 98 7654 3210      
//0011 1111 1111
//3    F    F
void Cell::Set(byte num)
{
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

boolean Cell::UnitTests()
{
  bool allPassed = false;

  //TODO

  return allPassed;
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

