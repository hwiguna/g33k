void RefreshCursor()
{
  if (millis() > timeToUpdateCursor) {
    cursorIsShown = !cursorIsShown;

//    Serial.print("cursorX="); Serial.print(cursorX);
//    Serial.print(" cursorY="); Serial.print(cursorY);
//    Serial.print(" cursorIsShown="); Serial.println(cursorIsShown);

    if (cursorIsShown)
      DrawCursor(cursorX, cursorY);
    else
      ReDrawCell();
    display.display();
    
    timeToUpdateCursor = millis() + 250; 
  }
}

void MoveCursor(int8_t xD, int8_t yD)
{
  //-- Replace cursor with the digit before moving cursor --
  if (cursorIsShown) {
    ReDrawCell();
    display.display();
  }
  
  cursorX += xD;
  cursorY += yD;
  if (cursorX>8) cursorX=0;
  if (cursorX<0) cursorX=8;
  if (cursorY>8) cursorY=0;
  if (cursorY<0) cursorY=8;
}

void DrawCursor(byte x, byte y)
{
  byte x0 = x*5 + CellOffset(x);
  byte y0 = y*6 + CellOffset(y);
  display.fillRect(x0, y0, 4,5, BLACK);
}
