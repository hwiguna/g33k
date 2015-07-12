/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif


//Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

uint8_t counter = 0;
String msg = "Hello YouTube!";

void setup() {
  //Serial.begin(9600);
  //Serial.println("HT16K33 test");

  pinMode(A0, INPUT);
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  matrix.fillScreen(0);

  int len = msg.length();
  int16_t reading = analogRead(A0);
  int16_t xOffset = map(reading, 0, 950, (len-1)*6, 0); // In theory upper should be 1023, but in practice it only reach 1000
  //matrix.drawPixel(x,7, 1);

  for (int i = 0; i < len; i++)
    matrix.drawChar(i*6 - xOffset, 0, msg[i], 1, 0, 1);

  // write the changes we just made to the display
  matrix.writeDisplay();
  delay(100);

  counter++;
  if (counter >= 8) counter = 0;
}
