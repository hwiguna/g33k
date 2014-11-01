class Scanner
{
  public:
    Scanner(Debug inDebug, Board board);
    void Solve();
  private:
    Debug debug;
    void FindCandidates();
};

Scanner::Scanner(Debug inDebug, Board board)
{
  debug = inDebug;
}

void Scanner::Solve()
{
  FindCandidates();
}

void Scanner::FindCandidates()
{
  // .. Iterate through all rows
  for (int row=0; row<9; row++)
  {
    for (int col=0; col<9; col++)
    {
      debug.DebugNum2("Scanning row,col=", row, col);
    }
  }
}

