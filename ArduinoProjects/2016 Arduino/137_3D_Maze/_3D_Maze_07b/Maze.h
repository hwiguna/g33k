//== Maze ==
byte maze[][1] = {
  {B11111111},
  {B10000001},
  {B10110111},
  {B10000111},
  {B11110001},
  {B10000101},
  {B10111101},
  {B11111111},
};

bool hasFrontLeftWall;
bool hasFrontWall;
bool hasFrontRightWall;
bool hasBackLeftWall;
bool hasBackWall;
bool hasBackRightWall;

bool Look(byte row, byte col)
{
  return bitRead(maze[row][0], 7 - col);
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

