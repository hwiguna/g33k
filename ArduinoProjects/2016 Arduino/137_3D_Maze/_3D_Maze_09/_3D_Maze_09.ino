// Arduino 3D Maze v0.7 by Hari Wiguna, 2016
// v0.4 - Draws real maze
// v0.5 - Move forward
// v0.6 - Buttons
// v0.6c - fixing front/back walls, hide what's obscured
// v0.7 - prevent walking through walls
// v00.7b - Animate the walk
// v0.8 - bigger maze
// v0.9 - Animate turning left/right

#include "U8glib.h"// LCD library
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

#include "Point.h" // Handy way to pass around X and Y as one variable
#include "Debug.h" // Prints variables to Serial Monitor
#include "Maze.h"  // The maze itself and routines to check where the walls are
#include "Sound.h" // Where the beep comes from
#include "Buttons.h" // Handles the pushbuttons
#include "Drawing.h" // Magic where the fake 3D happens

void setup(void) {
  Serial.begin(9600);
  SetupDrawing();
  SetupButtons();
}

void loop(void) {
  u8g.firstPage();
  do {
    CheckButtons();
    Animate();
    DrawMaze();
  } while ( u8g.nextPage() );
}
