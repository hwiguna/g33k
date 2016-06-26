byte upPin = 3;
byte downPin = 4;
byte leftPin = 6;
byte rightPin = 5;

u8g_uint_t hInset;

//== Animation ==
unsigned long timeToMove;
u8g_uint_t zoom = 0;
u8g_uint_t zoomDir = 0;
u8g_uint_t zoomSpeed = 2;
u8g_uint_t hShift = 0;
u8g_uint_t turnSpeed = 16; // higher = faster
int bumpCount;
int vShift = 1;

void SetupButtons() {
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
}

void TurnLeft()
{
  youRotDir = -1;
}

void TurnRight()
{
  youRotDir = +1;
}

void Bump()
{
  bumpCount = 3;
  vShift = 1;
  Click();
}

void MoveForward()
{
  if (youDir == 0 && youRow > 0              && !Look(youRow - 1, youCol)) youRowDir = -1; // Facing North
  if (youDir == 1 && youCol < (mazeColMax - 1) && !Look(youRow, youCol + 1)) youColDir = +1; // Facing East
  if (youDir == 2 && youRow < (mazeRowMax - 1) && !Look(youRow + 1, youCol)) youRowDir = +1; // Facing South
  if (youDir == 3 && youCol > 0              && !Look(youRow, youCol - 1)) youColDir = -1; // Facing West
  if (youRowDir == 0 && youColDir == 0)
    Bump();
  else {
    zoom = 0;
    zoomDir = +zoomSpeed;
  }
}

void MoveBackward()
{
  if (youDir == 0 && youRow < (mazeRowMax - 1) && !Look(youRow + 1, youCol)) youRowDir = +1; // Facing North
  if (youDir == 1 && youCol > 0              && !Look(youRow, youCol - 1)) youColDir = -1; // Facing East
  if (youDir == 2 && youRow > 0              && !Look(youRow - 1, youCol)) youRowDir = -1; // Facing South
  if (youDir == 3 && youCol < (mazeColMax - 1) && !Look(youRow, youCol + 1)) youColDir = +1; // Facing West
  if (youRowDir == 0 && youColDir == 0)
    Bump();
  else {
    zoom = hInset;
    zoomDir = -zoomSpeed;
  }
}

void AnimateTurningLeftRight()
{
  if (youRotDir != 0 && millis() > timeToMove) {
    hShift += turnSpeed;
    if ((hShift <= 0) || (hShift >= screenWidth))
    {
      hShift = 0;
      youDir += youRotDir;
      if (youDir < 0) youDir = 3;
      if (youDir > 3) youDir = 0;
      youRotDir = 0;
    }
    timeToMove = millis() + 30;
  }
}

void AnimateWalkingForwardBackward()
{
  if (zoomDir != 0 && millis() > timeToMove) {
    Click();
    zoom += zoomDir;
    if (zoom >= hInset || zoom <= 0)
    {
      zoom = 0;
      zoomDir = 0;
      youRow += youRowDir;
      youCol += youColDir;
      youRowDir = youColDir = 0;
    }
    timeToMove = millis() + 30;
  }
}

void AnimateBumpingIntoWall()
{
  if (bumpCount > 0  && millis() > timeToMove) {
    if (--bumpCount == 0) {
      vShift = 0;
    }
    else
      vShift = 1 - vShift;
    timeToMove = millis() + 50;
  }
}

void Animate()
{
  AnimateTurningLeftRight();
  AnimateWalkingForwardBackward();
  AnimateBumpingIntoWall();
}

void CheckButtons()
{
  if (youRowDir == 0 && youColDir == 0 && youRotDir == 0) { // Only allow movement if we're not moving/rotating
    if (!digitalRead(leftPin)) TurnLeft();
    if (!digitalRead(rightPin)) TurnRight();
    if (!digitalRead(upPin)) MoveForward();
    if (!digitalRead(downPin)) MoveBackward();
  }
}

void CheckEscape()
{
  // Only check escape when user is not moving
  if (zoomDir == 0) {
    // Has he reached one of the maze outside edges?
    if (youRow == 0 || youRow == (mazeRowMax - 1) || youCol == 0 || youCol == (mazeColMax - 1))
    {
      PlayWinningSong();
      ResetMaze();
    }

  }
}

