// Arduino Pong by Hari Wiguna, 2016
// v0.0 - draw ball
// v0.1 - move ball
// v0.2 - using millis(), move in Y direction too

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

//== Game Variables ==
u8g_uint_t courtWidth, courtHeight; // How wide and tall is our screen?
u8g_uint_t ballSize = 4;
u8g_uint_t ballX;
u8g_uint_t ballDirectionX = 1;
u8g_uint_t ballY;
u8g_uint_t ballDirectionY = 1;
unsigned long timeToMove; // Is it time to move the ball?
int animationSpeed = 20;

void MoveBall()
{
  // millis is how long since we power up the Arduino.
  if (millis() > timeToMove) { // Is it time to move the ball? if so, compute new ball position.
    ballX += ballDirectionX;
    if (ballX >= (courtWidth - ballSize) || ballX <= 0) ballDirectionX = -ballDirectionX;

    ballY += ballDirectionY;
    if (ballY >= (courtHeight - ballSize) || ballY <= 0) ballDirectionY = -ballDirectionY;

    timeToMove = millis() + animationSpeed; // Set the next time we'll need to move the ball again.
  }
}

void setup(void) {
  u8g.setRot180();  // flip screen (if necessary)
  courtWidth = u8g.getWidth();
  courtHeight =  u8g.getHeight();
}

void loop(void) {
  u8g.firstPage();
  do {
    u8g.drawBox(ballX, ballY, ballSize, ballSize);
    MoveBall();
  } while ( u8g.nextPage() );
}
