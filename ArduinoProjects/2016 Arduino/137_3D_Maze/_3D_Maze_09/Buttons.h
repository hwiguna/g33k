byte upPin = 3;
byte downPin = 4;
byte leftPin = 6;
byte rightPin = 5;

int youRow = 6, youCol = 9;
int youDir = 0, youRowDir = 0, youColDir = 0;

u8g_uint_t hInset;

//== Animation ==
unsigned long timeToMove;
u8g_uint_t zoom = 0;
u8g_uint_t zoomSpeed = 0;

void SetupButtons() {
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
}

void TurnLeft()
{
  if (--youDir < 0) youDir = 3;
}

void TurnRight()
{
  if (++youDir > 3) youDir = 0;
}

void MoveForward()
{
  if (youDir == 0 && youRow > 0              && !Look(youRow - 1, youCol)) youRowDir = -1; // Facing North
  if (youDir == 1 && youCol < (mazeColMax-1) && !Look(youRow, youCol + 1)) youColDir = +1; // Facing East
  if (youDir == 2 && youRow < (mazeRowMax-1) && !Look(youRow + 1, youCol)) youRowDir = +1; // Facing South
  if (youDir == 3 && youCol > 0              && !Look(youRow, youCol - 1)) youColDir = -1; // Facing West
  if (youRowDir == 0 && youColDir == 0)
    Beep();
  else {
    zoom = 0;
    zoomSpeed = 1;
  }
}

void MoveBackward()
{
  if (youDir == 0 && youRow < (mazeRowMax-1) && !Look(youRow + 1, youCol)) youRowDir = +1; // Facing North
  if (youDir == 1 && youCol > 0              && !Look(youRow, youCol - 1)) youColDir = -1; // Facing East
  if (youDir == 2 && youRow > 0              && !Look(youRow - 1, youCol)) youRowDir = -1; // Facing South
  if (youDir == 3 && youCol < (mazeColMax-1) && !Look(youRow, youCol + 1)) youColDir = +1; // Facing West
  if (youRowDir == 0 && youColDir == 0)
    Beep();
  else {
    zoom = hInset;
    zoomSpeed = -1;
  }
}

void Animate()
{
  if (zoomSpeed!=0 && millis() > timeToMove) {
    zoom += zoomSpeed;
    if (zoom >= hInset || zoom <= 0)
    {
      zoom=0;
      zoomSpeed = 0;
      youRow += youRowDir;
      youCol += youColDir;
      youRowDir=youColDir=0;
    }
    timeToMove = millis() + 30;
  }
}

void CheckButtons()
{
  int oldRow = youRow;
  int oldCol = youCol;
  int oldDir = youDir;

  if (youRowDir == 0 && youColDir == 0) { // Only allow movement if we're not moving/rotating
    if (!digitalRead(leftPin)) TurnLeft();
    if (!digitalRead(rightPin)) TurnRight();
    if (!digitalRead(upPin)) MoveForward();
    if (!digitalRead(downPin)) MoveBackward();

    if (youDir != oldDir) delay(200); // debounce rotate buttons
  }
}

