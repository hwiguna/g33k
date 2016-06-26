//== Maze ==
byte maze[][2] = {
  {B11111111,B11111111},
  {B10000001,B11111111},
  {B10110111,B11111111},
  {B10000110,B00001111},
  {B11110000,B11101111},
  {B10000101,B10001111},
  {B10111101,B10111111},
  {B11111111,B11111111},
};

byte mazeColMax = 16;
byte mazeRowMax = 8;

bool hasFrontLeftWall;
bool hasFrontWall;
bool hasFrontRightWall;
bool hasBackLeftWall;
bool hasBackWall;
bool hasBackRightWall;

bool Look(byte row, byte col)
{
  int colByte = col/8;
  return bitRead(maze[row][colByte], 7 - (col%8));
}

void LookNorth(byte row, byte col)
{
  hasFrontLeftWall = Look(row, col - 1);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall= Look(row, col + 1);
  hasBackLeftWall  = Look(row - 1, col - 1);
  hasBackWall      = Look(row - 1, col);
  hasBackRightWall = Look(row - 1, col + 1);
}

void LookEast(byte row, byte col)
{
  hasFrontLeftWall = Look(row - 1, col);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall= Look(row + 1, col);
  hasBackLeftWall  = Look(row - 1, col + 1);
  hasBackWall      = Look(row,  col + 1);
  hasBackRightWall = Look(row + 1, col + 1);
}

void LookSouth(byte row, byte col)
{
  hasFrontLeftWall = Look(row, col + 1);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall= Look(row, col - 1);
  hasBackLeftWall  = Look(row + 1, col + 1);
  hasBackWall      = Look(row + 1, col);
  hasBackRightWall = Look(row + 1, col - 1);
}

void LookWest(byte row, byte col)
{
  hasFrontLeftWall = Look(row + 1, col);
  hasFrontWall     = Look(row,     col);
  hasFrontRightWall= Look(row - 1, col);
  hasBackLeftWall  = Look(row + 1, col - 1);
  hasBackWall      = Look(row,     col - 1);
  hasBackRightWall = Look(row - 1, col - 1);
}

