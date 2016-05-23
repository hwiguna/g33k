// Arduino Pong
// Hari Wiguna, 2016

#include "U8glib.h"

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0/DataCommand = 9, Reset = 8

//== Pong variables ==
u8g_uint_t x;
u8g_uint_t y;
u8g_uint_t dx = -1;
u8g_uint_t dy = 1;
u8g_uint_t ballWidth = 4;
u8g_uint_t ballHeight = 4;
u8g_uint_t ballSpeed = 60; //25;
u8g_uint_t paddleWidth = 2;
u8g_uint_t paddleHeight = ballHeight * 3;
u8g_uint_t py0;
u8g_uint_t py1;
u8g_uint_t courtWidth;
u8g_uint_t courtHeight;
byte litePin = 7; //TODO: Kill
int liteBrightness = 100; //TODO: Kill
byte state = 0; // 0=wait, 1=playing, 2=gameover

unsigned long timeToMove = 0;

void drawPaddle(u8g_uint_t x, u8g_uint_t y)
{
  u8g.drawBox(x, y, paddleWidth, paddleHeight);
}

bool hitsPaddle(u8g_uint_t py)
{
  return (y > py) && ( y <= (py + paddleHeight));
}

void draw(void) {
  py0 = map( analogRead(A0), 0, 1023, 0, u8g.getHeight() - paddleHeight);
  drawPaddle(0, py0);

  py1 = map( analogRead(A0), 0, 1023, 0, u8g.getHeight() - paddleHeight);
  drawPaddle(courtWidth - paddleWidth, py1);

  //-- Draw court --
  u8g.drawHLine(0, 0, courtWidth);
  u8g.drawHLine(0, courtHeight - 1, courtWidth);

  // Draw Ball --
  u8g.drawBox(x, y, ballWidth, ballHeight);

  if (millis() > timeToMove) {
    x = x + dx;
    if ( (x <= 0) && hitsPaddle(py0) ) dx = -dx;
    if ( ((x + ballWidth) >= courtWidth) && hitsPaddle(py1)) dx = -dx;

    y = y + dy;
    if ( (y <= 0) || ((y + ballHeight) >= u8g.getHeight())) dy = -dy;

    timeToMove = millis() + ballSpeed;

    if (x < 0 || x > courtWidth) {
      state = 2; // display message
      timeToMove = millis() + 1000; // How long to display the message
    }
  }
}

void waitStart()
{
  dx = 0;
  dy = 0;
  x = -ballWidth;
  y = 0;
  if (analogRead(0) == 0) {
    state = 1;
    x = courtWidth / 2;
    y = courtHeight / 2;
    dx = 1;
    dy = 1;
  }
}

void setup(void) {
  // flip screen, if required
  u8g.setRot180();

  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

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

  pinMode(8, OUTPUT);

  //== Pong code ==
  courtWidth = u8g.getWidth();
  courtHeight = u8g.getHeight();
  x = courtWidth / 2;
  y = courtHeight / 2;

  pinMode(litePin, OUTPUT);
  //analogWrite(litePin,liteBrightness);
}

void declareWinner()
{
  if (millis() < timeToMove) {
    u8g.setFont(u8g_font_unifont);
    u8g.setFont(u8g_font_osb21);
    u8g.drawStr( 0, 22, "You Lose!");
  }
  else
    state = 0;
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    if (state == 0) waitStart();
    if (state == 1) draw();
    if (state == 2) declareWinner();
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  //delay(50);
}

