// Arduino 3D Maze v0.0 by Hari Wiguna, 2016

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13,11, 9,8,10);    // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

u8g_uint_t screenWidth, screenHeight;
u8g_uint_t hInset;
u8g_uint_t vInset;
u8g_uint_t wallHeight;
int potPin = A0;
u8g_uint_t shift;
unsigned long timeToMove;

void DrawMaze()
{
  if (millis() > timeToMove) {
      shift = map(analogRead(potPin),0,1023, -10,10);
      timeToMove = millis() + 50;
  }

  u8g.drawFrame(0,0, screenWidth,screenHeight);

  wallHeight = screenHeight - vInset - vInset;

  //-- Left Wall --
  u8g.drawLine(0,0, hInset-shift,vInset);
  u8g.drawVLine(hInset-shift,vInset, wallHeight);
  u8g.drawLine(hInset-shift, screenHeight-vInset, 0, screenHeight);

  //-- Right Flat --
  u8g.drawHLine(screenWidth-hInset-shift,vInset, hInset+shift);
  u8g.drawVLine(screenWidth-hInset-shift,vInset, wallHeight);
  u8g.drawHLine(screenWidth-hInset-shift,screenHeight-vInset, hInset+shift);

  //-- Second Right Wall --
  u8g_uint_t hInset2 = hInset + 10;
  u8g_uint_t vInset2 = vInset + 8;
  u8g_uint_t wallHeight2 = screenHeight - vInset2 - vInset2;
  u8g.drawLine(screenWidth-hInset2-shift,vInset2, screenWidth-hInset-shift,vInset);
  u8g.drawVLine(screenWidth-hInset2-shift,vInset2, wallHeight2);
  u8g.drawLine(screenWidth-hInset2-shift,screenHeight-vInset2, screenWidth-hInset-shift,screenHeight-vInset);

  //-- Back wall --
  u8g.drawHLine(hInset-shift,vInset2, screenWidth-hInset-hInset2);
  u8g.drawHLine(hInset-shift,screenHeight-vInset2, screenWidth-hInset-hInset2);
}

void setup(void) {
  u8g.setRot180();  // flip screen
  screenWidth = u8g.getWidth();
  screenHeight = u8g.getHeight();
  vInset = screenHeight/4;
  hInset = screenWidth/4;
}

void loop(void) {
  u8g.firstPage();
  do {
    DrawMaze();
  } while ( u8g.nextPage() );
}
