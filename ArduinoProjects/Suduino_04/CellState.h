const byte SOLVED_BIT = 15;

class CellState
{
public:
  void Set(byte num);
  byte Get();
  void AddCandidate(byte num);
  void RemoveCandidate(byte num);
  boolean IsSolved();
  void Solved();
  boolean Maybe(byte num);
  boolean UnitTests();
  void FindWinner();
private:
  int _vals;
};

void CellState::Set(byte num)
{
  if (num==0)
  {
    _vals = 0x01FF; //Not solved and 9 lowest bits on meaning all # are possible candidates
  }
  else
  {
    _vals = 0;
    bitSet(_vals, num );
    Solved();
  }
}

byte CellState::Get()
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

void CellState::AddCandidate(byte num)
{
  if (!IsSolved())
    bitSet(_vals, num);
}

void CellState::RemoveCandidate(byte num)
{
  if (!IsSolved()) {
    bitClear(_vals, num);
  }
}

boolean CellState::IsSolved()
{
  return bitRead(_vals, SOLVED_BIT) != 0;
}

void CellState::Solved()
{
  bitSet(_vals,SOLVED_BIT);
}

boolean CellState::Maybe(byte num)
{
  return bitRead( _vals, num) == 0;
}

boolean CellState::UnitTests()
{
  bool allPassed = false;

  //TODO

  return allPassed;
}

void CellState::FindWinner()
{
  if (!IsSolved())
  {
    byte candidateCount = 0;
    for (byte i=1; i<=9; i++)
    {
      if (bitRead(_vals,i)==1)
        candidateCount++;
    }
    if (candidateCount==1)
      Solved();
  }
}
