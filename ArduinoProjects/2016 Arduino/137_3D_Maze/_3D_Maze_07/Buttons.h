byte upPin = 3;
byte downPin = 4;
byte leftPin = 6;
byte rightPin = 5;

int youRow = 6, youCol = 1, youDir = 0, rowDir = -1, colDir = 0;

void TurnLeft()
{
  youDir--;
  if (youDir < 0) youDir = 3;
}

void TurnRight()
{
  youDir++;
  if (youDir > 3) youDir = 0;
}

void MoveForward()
{
  int prevRow=youRow, prevCol=youCol;
  if (youDir == 0 && youRow > 0 && !Look(youRow-1,youCol)) youRow--; // Facing North
  if (youDir == 1 && youCol < 7 && !Look(youRow,youCol+1)) youCol++; // Facing East
  if (youDir == 2 && youRow < 7 && !Look(youRow+1,youCol)) youRow++; // Facing South
  if (youDir == 3 && youCol > 0 && !Look(youRow,youCol-1)) youCol--; // Facing West
  if (youRow==prevRow && youCol==prevCol) Beep();
}

void MoveBackward()
{
  int prevRow=youRow, prevCol=youCol;
  if (youDir == 0 && youRow < 7 && !Look(youRow+1,youCol)) youRow++; // Facing North
  if (youDir == 1 && youCol > 0 && !Look(youRow,youCol-1)) youCol--; // Facing East
  if (youDir == 2 && youRow > 0 && !Look(youRow-1,youCol)) youRow--; // Facing South
  if (youDir == 3 && youCol < 7 && !Look(youRow,youCol+1)) youCol++; // Facing West
  if (youRow==prevRow && youCol==prevCol) Beep();
}

void CheckButtons()
{
  int oldRow = youRow;
  int oldCol = youCol;
  int oldDir = youDir;

  if (!digitalRead(leftPin)) TurnLeft();
  if (!digitalRead(rightPin)) TurnRight();
  if (!digitalRead(upPin)) MoveForward();
  if (!digitalRead(downPin)) MoveBackward();

  if (youRow != oldRow || youCol != oldCol || youDir != oldDir) {
    Serial.println("==============");
    Debug("youRow", youRow);
    Debug("youCol", youCol);
    Debug("youDir", youDir);
    delay(200);
  }
}

