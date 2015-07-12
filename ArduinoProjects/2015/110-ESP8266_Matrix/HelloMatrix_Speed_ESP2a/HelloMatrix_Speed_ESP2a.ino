#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Wire.pins(0,2); // <-- IMPORTANT!!! call this BEFORE initializing AdaFruit matrix (which calls wire.begin() with no parameters!
  matrix.begin(0x70);  // pass in the address
  
  matrix.drawPixel(0,0, 1); //x,y, Color (0=off)
  matrix.drawChar(0, 0, 'H', 1, 0, 1); // x,y, char, Foreground, Background, size
  matrix.drawChar(6, 0, 'e', 1, 0, 1);
  
  matrix.writeDisplay();  // Actually update the display
}

void loop() {
}
