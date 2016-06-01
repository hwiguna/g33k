// Arduino Pong v0.6
// by Hari Wiguna, 2016

#include "U8glib.h"
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10);    // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

//== Preferences ==
byte p0Pin = A1;
byte p1Pin = A0;
u8g_uint_t ballWidth = 4;
u8g_uint_t ballHeight = 4;
u8g_uint_t animationSpeed = 40; //25;
u8g_uint_t paddleWidth = 2;
u8g_uint_t paddleHeight = ballHeight * 3;

//== Game variables ==
u8g_uint_t courtWidth, courtHeight;
u8g_uint_t x, y;
u8g_uint_t dx, dy;
u8g_uint_t py0, py1;
unsigned long timeToMove = 0;

//== Methods ==
void drawPaddle(u8g_uint_t x, u8g_uint_t y)
{
  u8g.drawBox(x, y, paddleWidth, paddleHeight);
}

bool MissedPaddle(u8g_uint_t py)
{
  u8g_uint_t ballTop = y;
  u8g_uint_t ballBottom = y + ballHeight - 1;
  u8g_uint_t paddleTop = py;
  u8g_uint_t paddleBottom = py + paddleHeight - 1;
  return ballBottom < paddleTop || ballTop > paddleBottom;
}

void DrawCourt()
{
  u8g.drawHLine(0, 0, courtWidth);
  u8g.drawHLine(0, courtHeight - 1, courtWidth);
  byte dash = 3;
  for (byte y = 0; y < (courtHeight / dash / 2); y++)
  {
    u8g.drawVLine(courtWidth / 2, 2 + y * dash * 2, dash);
  }
}

void DrawBall()
{
  u8g.drawBox(x, y, ballWidth, ballHeight);
}

void BounceX()
{
  dx = -dx;
  Beep();
}

void Missp0() // Left player missed the ball, start ball at right paddle
{
  x = courtWidth - ballWidth - 1;
  y = py1 + (paddleHeight - ballHeight) / 2;
  dx = -1;
  tone(2, 523 / 2, 512); // NOTE_C5, 1000/16
  delay(2000);
}

void Missp1() // Right player missed the ball, start ball at left paddle
{
  x = 0;
  y = py0 + (paddleHeight - ballHeight) / 2;
  dx = +1;
  tone(2, 523 / 2, 512); // NOTE_C5, 1000/16
  delay(2000);
}

void MoveBall()
{
  if (millis() > timeToMove) {
    x = x + dx;
    if (x <= 0)
        if (MissedPaddle(py0)) Missp0(); else BounceX();

    if ((x + ballWidth) >= courtWidth)
        if (MissedPaddle(py1)) Missp1(); else BounceX();

    y = y + dy;
    if ( (y <= 0) || ((y + ballHeight) >= u8g.getHeight())) {
      dy = -dy;
      Beep();
    }
    timeToMove = millis() + animationSpeed;
  }
}

void Beep()
{
  tone(2, 523, 62); // NOTE_C5, 1000/16
}

void setup(void) {
  u8g.setRot180();  // flip screen

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  courtWidth = u8g.getWidth();
  courtHeight = u8g.getHeight();
  dx = 1;
  dy = 1;
}

void loop(void) {
  u8g.firstPage();

  do {
    py0 = map( analogRead(p0Pin), 0, 1023, 0, u8g.getHeight() - paddleHeight);
    drawPaddle(0, py0);

    py1 = map( analogRead(p1Pin), 0, 1023, 0, u8g.getHeight() - paddleHeight);
    drawPaddle(courtWidth - paddleWidth, py1);

    DrawCourt();
    DrawBall();
    MoveBall();
  } while ( u8g.nextPage() );

}

