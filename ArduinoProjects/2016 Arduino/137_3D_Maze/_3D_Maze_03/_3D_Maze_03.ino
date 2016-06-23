// Arduino 3D Maze v0.0 by Hari Wiguna, 2016

#include "U8glib.h"
#include "Point.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

u8g_uint_t screenWidth, screenHeight;
u8g_uint_t screenHalfWidth, screenHalfHeight;

u8g_uint_t hInset;
u8g_uint_t vInset;
u8g_uint_t wallHeight;
int potPin = A0;
u8g_uint_t shift;
unsigned long timeToMove;
const int steps = 3;
float centerX[steps];
float centerY[steps];
float ratio;
u8g_uint_t x0, y0;

byte maze[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};

void XToCorners(u8g_uint_t x, Point* points) {
  u8g_uint_t y = (u8g_uint_t)(1.0 * x * ratio);
  points[0].Set(x0 - x, y0 - y); // 0 = top left
  points[1].Set(x0 + x, y0 - y); // 1 = top right
  points[2].Set(x0 + x, y0 + y); // 2 = bottom right
  points[3].Set(x0 - x, y0 + y); // 3 = bottom left
}

void DrawWalls(Point* outer, Point* inner, byte x, byte y)
{
  bool hasLeftSideWall = maze[x - 1][y];
  bool hasRightSideWall = maze[x + 1][y];
  bool hasFrontWall    = maze[x][y + 1];
  bool hasLeftFrontWall = maze[x-1][y+1];
  bool hasRightFrontWall = maze[x+1][y+1];

  //-- Left Side Wall --
  if (hasLeftSideWall) {
    u8g.drawLine( outer[0].X - shift, outer[0].Y, inner[0].X - shift, inner[0].Y);
    u8g.drawVLine(inner[0].X - shift, inner[0].Y, inner[3].Y - inner[0].Y);
    u8g.drawLine( inner[0].X - shift, inner[3].Y, outer[3].X - shift, outer[3].Y);
  } else
  {
    //-- Left Front Wall --
    u8g.drawHLine(outer[0].X - shift, inner[0].Y, outer[0].X - inner[0].X + shift);
    u8g.drawVLine(inner[0].X - shift, inner[0].Y, inner[3].Y - inner[1].Y);
    u8g.drawHLine(outer[3].X - shift, inner[3].Y, outer[3].X - inner[3].X + shift);
  }

  //-- Back wall --
  if (hasFrontWall) {
    u8g.drawHLine(outer[0].X - shift, outer[0].Y, outer[1].X - outer[0].X);
    u8g.drawHLine(outer[3].X - shift, outer[3].Y, outer[2].X - outer[3].X);
  }

  //-- Right Side Wall --
  if (hasRightSideWall) {
    u8g.drawLine( outer[1].X - shift, outer[1].Y, inner[1].X - shift, inner[1].Y);
    u8g.drawVLine(inner[1].X - shift, inner[1].Y, inner[2].Y - inner[1].Y);
    u8g.drawLine( inner[2].X - shift, inner[2].Y, outer[2].X - shift, outer[2].Y);
  }
  else
  {
    u8g.drawHLine(inner[1].X - shift, inner[1].Y, outer[1].X - inner[1].X + shift);
    u8g.drawVLine(inner[1].X - shift, inner[1].Y, inner[2].Y - inner[1].Y);
    u8g.drawHLine(inner[2].X - shift, inner[2].Y, outer[2].X - inner[2].X + shift);
  }
}

void DrawMaze()
{
  if (millis() > timeToMove) {
    shift = 0; //map(analogRead(potPin), 0, 1023, -10, 10);
    timeToMove = millis() + 50;
  }

  u8g.drawFrame(0, 0, screenWidth, screenHeight);

  Point corners0[4];  XToCorners(screenHalfWidth - hInset * 0, corners0);
  Point corners1[4];  XToCorners(screenHalfWidth - hInset * 1, corners1);
  Point corners2[4];  XToCorners(screenHalfWidth - hInset * 2, corners2);
  Point corners3[4];  XToCorners(screenHalfWidth - hInset * 3, corners3);

  DrawWalls(corners0, corners1, 2, 7 );
  //DrawWalls(corners1, corners2, 2, 6 );
  //DrawWalls(corners2, corners3, 2, 5 );

  //  wallHeight = screenHeight - vInset - vInset;
  //  //-- Second Right Wall --
  //  u8g_uint_t hInset2 = hInset + 10;
  //  u8g_uint_t vInset2 = vInset + 8;
  //  u8g_uint_t wallHeight2 = screenHeight - vInset2 - vInset2;
  //  u8g.drawLine(screenWidth - hInset2 - shift, vInset2, screenWidth - hInset - shift, vInset);
  //  u8g.drawVLine(screenWidth - hInset2 - shift, vInset2, wallHeight2);
  //  u8g.drawLine(screenWidth - hInset2 - shift, screenHeight - vInset2, screenWidth - hInset - shift, screenHeight - vInset);
  //
  //  //-- Back wall --
  //  u8g.drawHLine(hInset - shift, vInset2, screenWidth - hInset - hInset2);
  //  u8g.drawHLine(hInset - shift, screenHeight - vInset2, screenWidth - hInset - hInset2);
}

void setup(void) {
  Serial.begin(9600);
  u8g.setRot180();  // flip screen
  screenWidth = u8g.getWidth();
  screenHeight = u8g.getHeight();
  x0 = screenHalfWidth = screenWidth / 2;
  y0 = screenHalfHeight = screenHeight / 2;
  vInset = screenHeight / 4;
  hInset = screenWidth / 8;

  ratio = 1.0 * screenHalfHeight / screenHalfWidth;
}

void loop(void) {
  u8g.firstPage();
  do {
    DrawMaze();
  } while ( u8g.nextPage() );
}
