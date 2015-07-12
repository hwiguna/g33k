//
// Hello YouTube! on ESP-12 and AdaFruit I2C LED Matrix
// Hari Wiguna, 2015
//

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int offset = 0;
String msg = " Hello YouTube! ";
int msgLength = msg.length();

void setup() {
  pinMode(A0, INPUT);
  Wire.pins(0,2); // <-- IMPORTANT!!! call this BEFORE initializing AdaFruit matrix (which calls wire.begin() with no parameters!
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  // Draw the message with increasing negative offset to "scroll" it
  for (int i = 0; i < msgLength; i++)
    matrix.drawChar(i*6 - offset, 0, msg[i], 1, 0, 1);

  matrix.writeDisplay();  // Actually update the display
  
  if (offset++ >= msgLength*6) offset = 0;

  // NOTE: ESP8266's ADC pin has a max of 1V that maps to 1023
  // See Voltage Divider in wiring diagram.
  int potentiometer = analogRead(A0);
  int dly = map(potentiometer, 0, 950, 300, 30); // In theory upper should be 1023, but in practice it only reach 1000
  delay(dly);
}
