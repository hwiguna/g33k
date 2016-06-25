// Arduino 3D Maze v0.0 by Hari Wiguna, 2016
// v0.4 - Draws real maze
// v0.5 - Move forward
// v0.6 - Buttons

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

#include "Point.h"
#include "Debug.h"
#include "Buttons.h"

//=== Preferences ==
int potPin = A0;

//== Screen ==
u8g_uint_t screenWidth, screenHeight;
u8g_uint_t screenHalfWidth, screenHalfHeight;

//== 3D calculations ==
u8g_uint_t hInset;
float ratio;
u8g_uint_t shift;
u8g_uint_t x0, y0;
const int steps = 3; // todo

//== Animation ==
unsigned long timeToMove;
unsigned long timeToDebug;
u8g_uint_t zoom = 0;
u8g_uint_t zoomSpeed = 1;

//== Maze ==
byte maze[][1] = {
  //  {B11110100},
  //  {B10000000},
  //  {B01010011},
  //  {B01010000},
  //  {B00000000},
  //  {B01010000},
  //  {B00010000},
  //  {B01000000},
  {B11111111},
  {B10000111},
  {B10110111},
  {B10000001},
  {B11110101},
  {B10000101},
  {B10111101},
  {B11111111},
};

bool hasLeftSideWall;
bool hasFrontWall;
bool hasRightSideWall;
bool hasLeftFrontWall;
bool hasBackWall;
bool hasRightFrontWall;

bool Look(byte row, byte col)
{
  return bitRead(maze[row][0], 7 - col);
}

void LookNorth(byte row, byte col)
{
  hasLeftSideWall   = Look(row, col - 1);
  hasFrontWall      = Look(row, col);
  hasRightSideWall  = Look(row, col + 1);
  hasLeftFrontWall  = Look(row - 1, col - 1);
  hasBackWall       = Look(row - 1, col);
  hasRightFrontWall = Look(row - 1, col + 1);
}

void LookSouth(byte row, byte col)
{
  hasLeftSideWall   = Look(row, col + 1);
  hasFrontWall      = Look(row, col);
  hasRightSideWall  = Look(row, col - 1);
  hasLeftFrontWall  = Look(row + 1, col + 1);
  hasBackWall       = Look(row + 1, col);
  hasRightFrontWall = Look(row + 1, col - 1);
}

void LookWest(byte row, byte col)
{
  hasLeftSideWall   = Look(row + 1, col);
  hasFrontWall      = Look(row,  col);
  hasRightSideWall  = Look(row - 1, col);
  hasLeftFrontWall  = Look(row - 1, col - 1);
  hasBackWall       = Look(row,  col - 1);
  hasRightFrontWall = Look(row - 1, col - 1);
}

void LookEast(byte row, byte col)
{
  hasLeftSideWall   = Look(row - 1, col);
  hasFrontWall      = Look(row,  col);
  hasRightSideWall  = Look(row + 1, col);
  hasLeftFrontWall  = Look(row + 1, col + 1);
  hasBackWall       = Look(row,  col + 1);
  hasRightFrontWall = Look(row + 1, col + 1);
}

void XToCorners(u8g_uint_t x, Point* points) {
  u8g_uint_t y = (u8g_uint_t)(1.0 * x * ratio);
  points[0].Set(x0 - x, y0 - y); // 0 = top left
  points[1].Set(x0 + x, y0 - y); // 1 = top right
  points[2].Set(x0 + x, y0 + y); // 2 = bottom right
  points[3].Set(x0 - x, y0 + y); // 3 = bottom left
}

void DrawLeftSideWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, outs[0].Y, ins[0].X, ins[0].Y);
  u8g.drawLine(ins[0].X, ins[0].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, outs[3].X, outs[3].Y);
}

void DrawLeftFrontWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, ins[0].Y, ins[0].X, ins[0].Y);
  u8g.drawLine(ins[0].X, ins[0].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, outs[3].X, ins[3].Y);
}

void DrawFrontWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, outs[0].Y, outs[1].X, outs[1].Y);
  u8g.drawLine(outs[1].X, outs[1].Y, outs[2].X, outs[2].Y);
  u8g.drawLine(outs[2].X, outs[2].Y, outs[3].X, outs[3].Y);
  u8g.drawLine(outs[3].X, outs[3].Y, outs[0].X, outs[0].Y);
}

void DrawBackWall(Point* outs, Point* ins)
{
  u8g.drawLine(ins[0].X, ins[0].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, ins[0].X, ins[0].Y);
}

void DrawRightSideWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[1].X, outs[1].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, outs[2].X, outs[2].Y);
}

void DrawRightFrontWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[1].X, ins[1].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, outs[2].X, ins[2].Y);
}

void DrawWalls(byte depth, byte col, byte row)
{
  Point outs[4], ins[4];
  XToCorners(screenHalfWidth - hInset * depth       + (depth == 0 ? 0 : zoom), outs);
  XToCorners(screenHalfWidth - hInset * (depth + 1) + zoom, ins);

  if (youDir==0) LookNorth(row,col);
  if (youDir==1) LookWest(row, col);
  if (youDir==2) LookSouth(row,col);
  if (youDir==3) LookEast(row,col);

  if (hasFrontWall)
    DrawFrontWall(outs, ins);
  else
  {
    if (hasBackWall) DrawBackWall(outs, ins);

    if (hasLeftSideWall) DrawLeftSideWall(outs, ins);
    else if (hasLeftFrontWall) DrawLeftFrontWall(outs, ins);

    if (hasRightSideWall) DrawRightSideWall(outs, ins);
    else if (hasRightFrontWall) DrawRightFrontWall(outs, ins);
  }
}

void DrawMaze()
{
  u8g.drawFrame(0, 0, screenWidth, screenHeight);

  for (byte depth = 0; depth < 3; depth++)
    DrawWalls(depth, youCol, youRow - depth);
}

void MoveNorth()
{
  youRow -= rowDir; if (youRow < 0) youRow = 7;
}

void MoveSouth()
{
  youRow += rowDir; if (youRow > 7) youRow = 0;
}

void MoveEast()
{
  youCol += colDir; if (youCol > 7) youCol = 0;
}

void MoveWest()
{
  youCol -= colDir; if (youCol < 0) youCol = 7;
}

void Move()
{
  if (millis() > timeToMove) {
    zoom += zoomSpeed;
    if (zoom >= hInset)
    {
      zoom = 0;
      //      MoveNorth();
      //    MoveSouth();
      //    MoveEast();
      //    MoveWest();
    }
    timeToMove = millis() + 100;
  }
}

void setup(void) {
  Serial.begin(9600);
  u8g.setRot180();  // flip screen
  screenWidth = u8g.getWidth();
  screenHeight = u8g.getHeight();
  x0 = screenHalfWidth = screenWidth / 2;
  y0 = screenHalfHeight = screenHeight / 2;
  hInset = screenWidth / 7;
  ratio = 1.0 * screenHalfHeight / screenHalfWidth;
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
}

void loop(void) {
  u8g.firstPage();
  do {
    CheckButtons();
    DrawMaze();
  } while ( u8g.nextPage() );
}
