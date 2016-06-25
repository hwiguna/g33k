// Arduino 3D Maze v0.0 by Hari Wiguna, 2016
// v0.4 - Draws real maze
// v0.5 - Move forward
// v0.6 - Buttons
// v0.6c - fixing front/back walls, hide what's obscured
// v0.7 - prevent walking through walls

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

#include "Point.h"
#include "Debug.h"
#include "Maze.h"
#include "Sound.h"
#include "Buttons.h"
#include "Drawing.h"

void Move()
{
  if (millis() > timeToMove) {
    zoom += zoomSpeed;
    if (zoom >= hInset)
    {
      zoom = 0;
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
