//== Maze ==
byte maze[][2] = {
  {B11111111, B11110111},
  {B11000000, B11110111},
  {B11111011, B10000001},
  {B11111011, B11010111},
  {B10000011, B11000001},
  {B11011011, B11110111},
  {B10000000, B00000111},
  {B11111111, B11111111},
};

byte mazeColMax = 16;
byte mazeRowMax = 8;

#define FacingNorth 0
#define FacingEast 1
#define FacingSouth 2
#define FacingWest 3

int youRow, youCol; // Where you are in the Maze
int youDir = 0; // Facing 0=North, 1=East, 3=South, 3=West
int youRotDir = 0; // Turning -1=Left, 0=none, 1=Right
int youRowDir = 0, youColDir = 0; // Delta when walking

bool hasFrontLeftWall;
bool hasFrontWall;
bool hasFrontRightWall;
bool hasBackLeftWall;
bool hasBackWall;
bool hasBackRightWall;

void ResetMaze()
{
  youCol = 12;
  youRow = 3;
  youDir = FacingNorth;
}

bool Look(byte row, byte col)
{
  if (row < 0 || row > mazeRowMax || col < 0 || col > mazeColMax)
    return false;
  else
  {
    int colByte = col / 8;
    return bitRead(maze[row][colByte], 7 - (col % 8));
  }
}

void LookNorth(byte row, byte col)
{
  hasFrontLeftWall = Look(row, col - 1);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall = Look(row, col + 1);
  hasBackLeftWall  = Look(row - 1, col - 1);
  hasBackWall      = Look(row - 1, col);
  hasBackRightWall = Look(row - 1, col + 1);
}

void LookEast(byte row, byte col)
{
  hasFrontLeftWall = Look(row - 1, col);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall = Look(row + 1, col);
  hasBackLeftWall  = Look(row - 1, col + 1);
  hasBackWall      = Look(row,  col + 1);
  hasBackRightWall = Look(row + 1, col + 1);
}

void LookSouth(byte row, byte col)
{
  hasFrontLeftWall = Look(row, col + 1);
  hasFrontWall     = Look(row, col);
  hasFrontRightWall = Look(row, col - 1);
  hasBackLeftWall  = Look(row + 1, col + 1);
  hasBackWall      = Look(row + 1, col);
  hasBackRightWall = Look(row + 1, col - 1);
}

void LookWest(byte row, byte col)
{
  hasFrontLeftWall = Look(row + 1, col);
  hasFrontWall     = Look(row,     col);
  hasFrontRightWall = Look(row - 1, col);
  hasBackLeftWall  = Look(row + 1, col - 1);
  hasBackWall      = Look(row,     col - 1);
  hasBackRightWall = Look(row - 1, col - 1);
}

