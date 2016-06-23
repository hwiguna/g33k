// Arduino Pong v0.0 by Hari Wiguna, 2016

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13,11, 9,8,10);    // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

void setup(void) {
  u8g.setRot180();  // flip screen
}

void loop(void) {
  u8g.firstPage();
  do {
    u8g.drawBox(0,0, 4,4);
    u8g.drawLine(50,50, -10,0);
  } while ( u8g.nextPage() );
}
