class Scanner
{
  public:
    Scanner(Debug inDebug, Board board);
    void Solve();
  private:
    Debug debug;
    Board board;
    void FindCandidates();
};

Scanner::Scanner(Debug inDebug, Board inBoard)
{
  debug = inDebug;
  board = inBoard;
}

void Scanner::Solve()
{
  FindCandidates();
}

void Scanner::FindCandidates()
{
  // .. Iterate through all rows
  for (byte y=0; y<9; y++)
  {
    for (byte x=0; x<9; x++)
    {
      debug.DebugNum2("Scanning x,y=", x, y);
      if (!board.GetCell(x,y).IsSolved())
      {
        CheckY(y);
      }
    }
  }
}

void Scanner::CheckY(byte y)
{
  for (byte x=0; x<9; x++)
  {
    if (board.Getcell(x,y).IsSolved() {
        for (byte x2=0; x2<9; x2++)
        {
          board.Getcell(x,y).IsSolved()
        }
    }
  }
}

