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

byte wallX[4][4] = {
  {0,0,0,0}, // X
  {0,0,0,0}, // |
  {1,0,0,0}, // |
  {1,0,0,0}  // V
};
byte wallY[4][4] = {
  {0,0,0,0}, // Y
  {0,0,0,0}, // |
  {0,0,1,0}, // |
  {0,0,0,0}  // V
};

void XToCorners(u8g_uint_t x, Point* points) {
  u8g_uint_t y = (u8g_uint_t)(1.0 * x * ratio);
  points[0].Set(x0 - x, y0 - y); // 0 = top left
  points[1].Set(x0 + x, y0 - y); // 1 = top right
  points[2].Set(x0 + x, y0 + y); // 2 = bottom right
  points[3].Set(x0 - x, y0 + y); // 3 = bottom left
}

void DrawWalls(Point* corners0, Point* corners1, byte x, byte y)
{
  bool hasLeftSideWall = wallX[x][y];
  bool hasLeftFrontWall = wallY[x-1][y]; //maze[x - 1][y][frontIndex];
  bool hasFrontWall = wallY[x][y];
  bool hasRightFrontWall = wallY[x+1][y];
  bool hasRightSideWall = wallX[x+1][y];

  //-- Left Side Wall --
  if (hasLeftSideWall) {
      u8g.drawLine(corners0[0].X - shift, corners0[0].Y, corners1[0].X - shift, corners1[0].Y);
      u8g.drawVLine(corners1[0].X - shift, corners1[0].Y, corners1[3].Y - corners1[0].Y);
      u8g.drawLine(corners1[0].X - shift, corners1[3].Y, corners0[0].X - shift, corners0[3].Y);
  }

  //-- Back wall --
  if (hasFrontWall) {
    u8g.drawHLine(corners0[0].X - shift, corners0[0].Y, corners1[1].X-corners0[0].X);
    u8g.drawHLine(corners0[0].X - shift, corners0[3].Y, corners1[1].X-corners0[0].X);
  }

  //-- Right Side Wall --
  if (hasRightSideWall) {
      u8g.drawLine(corners0[1].X - shift, corners0[1].Y, corners1[1].X - shift, corners1[1].Y);
      u8g.drawVLine(corners1[1].X - shift, corners1[1].Y, corners1[3].Y - corners1[1].Y);
      u8g.drawLine(corners1[1].X - shift, corners1[3].Y, corners0[2].X - shift, corners0[2].Y);
  }


//  //-- Right Flat --
//  if (onRight == 2) {
//    u8g.drawHLine(screenWidth - hInset - shift, vInset, hInset + shift);
//    u8g.drawVLine(screenWidth - hInset - shift, vInset, wallHeight);
//    u8g.drawHLine(screenWidth - hInset - shift, screenHeight - vInset, hInset + shift);
//  }

}

void DrawMaze()
{
  if (millis() > timeToMove) {
    shift = map(analogRead(potPin), 0, 1023, -10, 10);
    timeToMove = millis() + 50;
  }

  u8g.drawFrame(0, 0, screenWidth, screenHeight);

  Point corners0[4];  XToCorners(screenHalfWidth - hInset*0, corners0);
  Point corners1[4];  XToCorners(screenHalfWidth - hInset*1, corners1);
  Point corners2[4];  XToCorners(screenHalfWidth - hInset*2, corners2);
  Point corners3[4];  XToCorners(screenHalfWidth - hInset*3, corners3);

  DrawWalls(corners0, corners1, 2,0 );
  DrawWalls(corners1, corners2, 2,1 );
  DrawWalls(corners2, corners3, 2,2 );

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
