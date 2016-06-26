// Arduino 3D Maze v0.7 by Hari Wiguna, 2016
// v0.4 - Draws real maze
// v0.5 - Move forward
// v0.6 - Buttons
// v0.6c - fixing front/back walls, hide what's obscured
// v0.7 - prevent walking through walls
// v00.7b - Animate the walk
// v0.8 - bigger maze
// v0.9 - Animate turning left/right
// v0.10 - Detect Success, play winning song, fixed bugs

//== Screen ==
#include "U8glib.h"// LCD library
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10
u8g_uint_t screenWidth, screenHeight;
u8g_uint_t screenHalfWidth, screenHalfHeight;

//== See other tabs above... ==
#include "Point.h" // Handy way to pass around X and Y as one variable
#include "Debug.h" // Prints variables to Serial Monitor
#include "Maze.h"  // The maze itself and routines to check where the walls are
#include "Sound.h" // Where the beep comes from
#include "Buttons.h" // Handles the pushbuttons
#include "Drawing.h" // Magic where the fake 3D happens

void setup(void) {
  Serial.begin(9600); // Only used for debugging
  ResetMaze();        // Setup initial player position & facing direction
  SetupDrawing();     // Get screen size, horiz vs vert ratio
  SetupButtons();     // Setup pushbutton I/O pin modes to input with internal pullup resistor
}

void loop(void) {
  CheckEscape();  // Have user reached any of the maze edges?
  CheckButtons(); // Handle user pushbuttons
  Animate();      // Compute animation variables

  // This u8g loop updates the screen (calling DrawMaze multiple times if necessary)
  u8g.firstPage();
  do {
    DrawMaze();   // Draw the maze (incorporating the animation parameters)
  } while ( u8g.nextPage() );
}
