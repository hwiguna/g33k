byte upPin = 3;
byte downPin = 4;
byte leftPin = 6;
byte rightPin = 5;

u8g_uint_t youRow = 6, youCol = 1, youDir=0, rowDir = -1, colDir = 0;

void TurnLeft()
{
  youDir--;
  if (youDir<0) youDir=3;
}

void TurnRight()
{
  youDir++;
  if (youDir>3) youDir=0;
}

void MoveForward()
{
  if (youDir==0 && youRow>0) youRow--; // Facing North
  if (youDir==1 && youCol<8) youCol++; // Facing East
  if (youDir==2 && youRow<8) youRow++; // Facing South
  if (youDir==3 && youCol>0) youCol--; // Facing West
}

void GoHome()
{
  youRow=6;
  youCol=1;
  youDir=0;
}

void CheckButtons()
{
  if (!digitalRead(leftPin)) TurnLeft();
  if (!digitalRead(rightPin)) TurnRight();
  if (!digitalRead(upPin)) MoveForward();
  if (!digitalRead(downPin)) GoHome();
}

