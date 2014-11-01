const byte SOLVED_BIT = 15;

class CellState
{
public:
  CellState();

  void Set(char ch);
  char Get();
  void AddCandidate(int num);
  void AddCandidate(char ch);
  void Remove(char ch);
  boolean IsSolved();
  boolean Maybe(char ch);
  boolean UnitTests();
  int CharToNum(char ch);
private:
  int _vals;
};

CellState::CellState()
{
}

void CellState::Set(char ch)
{
  _vals = 0;
  bitSet(_vals, CharToNum(ch) );
}

char CellState::Get()
{
  char ch = '*';
  if (IsSolved())
  {
    for (byte i=1; i<=9; i++)
    {
      if (bitRead(_vals,i)) {
        ch = '0' + i;
        break;
      }
    }
  }
  return ch;
}

void CellState::AddCandidate(int num)
{
  if (!IsSolved())
    bitClear(_vals, num);
}

boolean CellState::IsSolved()
{
  return bitRead(_vals, SOLVED_BIT) != 0;
}

void CellState::AddCandidate(char ch)
{
  AddCandidate( CharToNum(ch) );
}

boolean CellState::Maybe(char ch)
{
  return bitRead( _vals, CharToNum(ch)) == 0;
}

boolean CellState::UnitTests()
{
  bool allPassed = false;

  //TODO

  return allPassed;
}

int CellState::CharToNum(char ch)
{
  int num;
  if (ch=='*') num = 0; else num = ch-48;
  return num;
}
