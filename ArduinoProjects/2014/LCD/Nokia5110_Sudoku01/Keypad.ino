void ScanKeypad()
{
  // Power up one column at a time
  for (byte col=0; col<4; col++)
  {
    digitalWrite(col3Pin+col, LOW); // LOW = ON
    // Check to see if that power made it to one of the rows
    for (byte row=0; row<4; row++)
    {
      byte val = digitalRead(row0Pin+row);
      if (val==LOW) {
        //Serial.print("row="); Serial.print(row);
        //Serial.print(" col="); Serial.print(3-col);
        //Serial.print(" key="); Serial.println(keys[row][3-col]);
        ProcessKeypress(keys[row][3-col]);
        delay(200);
      }
    }
    digitalWrite(col3Pin+col, HIGH); // LOW = OFF
  }
}

void ProcessKeypress(char key)
{
  switch (key)
  {
    case 'A': MoveCursor(+1,0); break;
    case 'B': MoveCursor(-1,0); break;
    case 'C': MoveCursor(0,-1); break;
    case 'D': MoveCursor(0,+1); break;
    case '#': FakeSolve(); break;
    default: 
      SetCell(cursorX,cursorY, key);
      ReDrawCell();
      
      //-- Auto advance cursor to next char, next row, and wrap back to 0,0
      if (cursorX==8) {
        cursorX=0;
        if (++cursorY>8) cursorY=0;
      }
      else
        MoveCursor(1,0);
      break;
  }
}
