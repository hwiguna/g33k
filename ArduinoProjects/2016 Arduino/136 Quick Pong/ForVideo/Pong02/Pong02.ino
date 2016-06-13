// Arduino Pong by Hari Wiguna, 2016
// v0.0 - draw ball
// v0.1 - move ball
// v0.2 - using millis(), move in Y direction too

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10); // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

//== Game Variables ==
u8g_uint_t courtWidth, courtHeight;
u8g_uint_t ballSize = 4;
u8g_uint_t ballX;
u8g_uint_t ballDirectionX = 1;
u8g_uint_t ballY;
u8g_uint_t ballDirectionY = 1;
unsigned long timeToMove;
int animationSpeed = 20;

void MoveBall()
{
  if (millis() > timeToMove) {
    ballX += ballDirectionX;
    if (ballX >= (courtWidth - ballSize) || ballX <= 0) ballDirectionX = -ballDirectionX;

    ballY += ballDirectionY;
    if (ballY >= (courtHeight - ballSize) || ballY <= 0) ballDirectionY = -ballDirectionY;

    timeToMove = millis() + animationSpeed;
  }
}

void setup(void) {
  u8g.setRot180();  // flip screen
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
