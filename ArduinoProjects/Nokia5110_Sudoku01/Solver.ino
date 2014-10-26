void FakeSolve()
{
  byte num = 1;
  for (byte x=0; x<9; x++)
  {
    for (byte y=0; y<9; y++)
    {
      cursorX = x;
      cursorY = y;
      if (board[x][y]=='*') {
        SetCell(x,y, '0' + random(1,9));
        ReDrawCell();
      }
    }
  }
  display.display();
}
