byte CellOffset(byte x)
{
  return ((x>2) ? 2 : 0) + ((x>5) ? 2 : 0);
}

void ReDrawCell()
{
  EraseCell(cursorX, cursorY);
  DrawCell(cursorX, cursorY);
}

void SetCell(byte x, byte y, char val)
{
  board[x][y] = val;
}

void EraseCell(byte x, byte y)
{
  byte x0 = x*5 + CellOffset(x);
  byte y0 = y*6 + CellOffset(y);
  display.fillRect(x0, y0, 4,5, WHITE);
}

void DrawBoard()
{
  byte num = 1;
  for (byte x=0; x<9; x++)
  {
    //byte xD = ((x>2) ? 2 : 0) + ((x>5) ? 2 : 0);
    for (byte y=0; y<9; y++)
    {
      //byte yD = ((y>2) ? 2 : 0) + ((y>5) ? 2 : 0);
      num = random(1,9);
      //DrawCell(x,y, '*');
      DrawCell(x,y);
    }
  }
  display.display();
}

void DrawCell(int16_t x, int16_t y)
{
  DrawCell(x, y, board[x][y]);
}

void DrawCell(int16_t x, int16_t y, char ch)
{
  x = x*5 + CellOffset(x); 
  y = y*6 + CellOffset(y); 
  int16_t w=3;
  int16_t h=4;
  uint16_t color = BLACK;

  switch (ch)
  {
  case '0':
    display.drawRect(x,y, w+1,h+1, color);
    break;
  case '1':
    display.drawLine(x+2,y, x+2, y+h, color);
    break;
  case '2':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+2, color);
    display.drawLine(x,y+h-2, x, y+h, color);
    break;
  case '3':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '4':
    // horizontals
    display.drawLine(x,y+2, x+w, y+2, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '5':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y+h-2, x+w, y+h, color);
    break;
  case '6':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+h, color);
    display.drawLine(x+w,y+h-2, x+w, y+h, color);
    break;
  case '7':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    // verticals
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '8':
    display.drawRect(x,y, w+1,h+1, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    break;
  case '9':
    // horizontals
    display.drawLine(x,y, x+w, y, color);
    display.drawLine(x,y+2, x+w, y+2, color);
    display.drawLine(x,y+h, x+w, y+h, color);
    // verticals
    display.drawLine(x,y, x, y+2, color);
    display.drawLine(x+w,y, x+w, y+h, color);
    break;
  case '*':
//    display.drawPixel(x,y, color);
//    display.drawPixel(x,y+h, color);
//    display.drawPixel(x+w,y, color);
//    display.drawPixel(x+w,y+h, color);
    display.drawLine(x+1,y+2, x+2, y+2, color);
    break;
  default:
    display.drawRect(x,y, w+1,h+1, color);
    break;
  }
}

