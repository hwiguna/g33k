// Arduino 3D Maze v0.0 by Hari Wiguna, 2016
// v0.4 - Draws real maze
// v0.5 - Move forward

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

#include "Point.h"
#include "Debug.h"

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
Point corners[5][4];
const int steps = 3; // todo

//== Animation ==
unsigned long timeToMove;
unsigned long timeToDebug;
u8g_uint_t zoom = 0;
u8g_uint_t zoomSpeed = 1;

//== Maze ==
byte maze[][1] = {
  {B01110000},
  {B00000000},
  {B01010000},
  {B01000000},
  {B00000000},
  {B01010000},
  {B00010000},
  {B01000000},
};
u8g_uint_t youCol=2, youRow=7, rowDir=-1;

void XToCorners(u8g_uint_t x, Point* points) {
  u8g_uint_t y = (u8g_uint_t)(1.0 * x * ratio);
  points[0].Set(x0 - x, y0 - y); // 0 = top left
  points[1].Set(x0 + x, y0 - y); // 1 = top right
  points[2].Set(x0 + x, y0 + y); // 2 = bottom right
  points[3].Set(x0 - x, y0 + y); // 3 = bottom left
}

void DrawWalls(Point* outer, Point* inner, byte col, byte row)
{
  bool hasLeftSideWall   = bitRead(maze[row][0], 7 - (col - 1));
  bool hasFrontWall      = bitRead(maze[row][0], 7 - col);
  bool hasRightSideWall  = bitRead(maze[row][0], 7 - (col + 1));
  bool hasLeftFrontWall  = bitRead(maze[row - 1][0], 7 - (col - 1));
  bool hasBackWall       = bitRead(maze[row - 1][0], 7 - col);
  bool hasRightFrontWall = bitRead(maze[row - 1][0], 7 - (col + 1));

  //-- Left Side Wall --
  if (hasLeftSideWall) {
    u8g.drawLine(outer[0].X, outer[0].Y, inner[0].X, inner[0].Y);
    u8g.drawLine(inner[0].X, inner[0].Y, inner[3].X, inner[3].Y);
    u8g.drawLine(inner[3].X, inner[3].Y, outer[3].X, outer[3].Y);
  }
  else
  {
    //-- No Left Wall --
    if (hasLeftFrontWall) {
      u8g.drawLine(outer[0].X, inner[0].Y, inner[0].X, inner[0].Y);
      u8g.drawLine(inner[0].X, inner[0].Y, inner[3].X, inner[3].Y);
      u8g.drawLine(inner[3].X, inner[3].Y, outer[3].X, inner[3].Y);
    }
  }

  //-- Front wall --
  if (hasFrontWall) {
    u8g.drawLine(outer[0].X, outer[0].Y, outer[1].X, outer[1].Y);
    u8g.drawLine(outer[1].X, outer[1].Y, outer[2].X, outer[2].Y);
    u8g.drawLine(outer[2].X, outer[2].Y, outer[3].X, outer[3].Y);
    u8g.drawLine(outer[3].X, outer[3].Y, outer[0].X, outer[0].Y);
  } else
  {
    if (hasBackWall) {
      u8g.drawLine(inner[0].X, inner[0].Y, inner[1].X, inner[1].Y);
      u8g.drawLine(inner[1].X, inner[1].Y, inner[2].X, inner[2].Y);
      u8g.drawLine(inner[2].X, inner[2].Y, inner[3].X, inner[3].Y);
      u8g.drawLine(inner[3].X, inner[3].Y, inner[0].X, inner[0].Y);
    }
  }

  //-- Right Side Wall --
  if (hasRightSideWall) {
    u8g.drawLine(outer[1].X, outer[1].Y, inner[1].X, inner[1].Y);
    u8g.drawLine(inner[1].X, inner[1].Y, inner[2].X, inner[2].Y);
    u8g.drawLine(inner[2].X, inner[2].Y, outer[2].X, outer[2].Y);
  }
  else
  {
    //-- No Right Wall --
    if (hasRightFrontWall) {
      u8g.drawLine(outer[1].X, inner[1].Y, inner[1].X, inner[1].Y);
      u8g.drawLine(inner[1].X, inner[1].Y, inner[2].X, inner[2].Y);
      u8g.drawLine(inner[2].X, inner[2].Y, outer[2].X, inner[2].Y);
    }
  }
}

void DrawMaze()
{
    if (millis() > timeToMove) {
       zoom += zoomSpeed;
       if (zoom>=hInset)
       {
        zoom=0;
        youRow += rowDir;
        if (youRow<1) {youRow=7; }
        //if (youRow>7) {youRow=7; rowDir=-1; zoomSpeed=+1;}
       }

      XToCorners(screenHalfWidth - hInset * 0       , corners[0]);
      XToCorners(screenHalfWidth - hInset * 1 + zoom, corners[1]);
      XToCorners(screenHalfWidth - hInset * 2 + zoom, corners[2]);
      XToCorners(screenHalfWidth - hInset * 3 + zoom, corners[3]);
    
      timeToMove = millis() + 100;
    }

  u8g.drawFrame(0, 0, screenWidth, screenHeight);

  DrawWalls(corners[0], corners[1], youCol, youRow);
  DrawWalls(corners[1], corners[2], youCol, youRow-1);
  DrawWalls(corners[2], corners[3], youCol, youRow-2);
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
}

void loop(void) {
  u8g.firstPage();
  do {
    DrawMaze();
  } while ( u8g.nextPage() );
}
