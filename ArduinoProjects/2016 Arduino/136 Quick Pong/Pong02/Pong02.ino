// Arduino Pong
// Hari Wiguna, 2016

// v2 - instant replay

#include "U8glib.h"

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0/DataCommand = 9, Reset = 8

//== Pong variables ==
u8g_uint_t x;
u8g_uint_t y;
u8g_uint_t dx = -1;
u8g_uint_t dy = 1;
u8g_uint_t ballWidth = 4;
u8g_uint_t ballHeight = 4;
u8g_uint_t animationSpeed = 60; //25;
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
const int tapeMax = 10;
int tapePos = tapeMax; // Index to the last recorded element
u8g_uint_t tapePy0[tapeMax];
u8g_uint_t tapePy1[tapeMax];
u8g_uint_t tapeX[tapeMax];
u8g_uint_t tapeY[tapeMax];

void drawPaddle(u8g_uint_t x, u8g_uint_t y)
{
  u8g.drawBox(x, y, paddleWidth, paddleHeight);
}

bool hitsPaddle(u8g_uint_t py)
{
  return (y > py) && ( y <= (py + paddleHeight));
}

void draw() {
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

    //-- Record Positions --
    tapePos--;
    if (tapePos < 0) tapePos = tapeMax - 1;
    tapePy0[tapePos] = py0;
    tapePy1[tapePos] = py1;
    tapeX[tapePos] = x;
    tapeY[tapePos] = y;
    Serial.print("tapePos=");
    Serial.println(tapePos);

    timeToMove = millis() + animationSpeed;

    if (x < 0 || x > courtWidth) {
      state = 2; // Instant Replay
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
  Serial.begin(9600);

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
  Serial.print("courtWidth=");
  Serial.println(courtWidth);
  courtHeight = u8g.getHeight();
  x = courtWidth / 2;
  y = courtHeight / 2;

  pinMode(litePin, OUTPUT);
  //analogWrite(litePin,liteBrightness);
  Serial.println("start");
}

void DrawFrame(int f)
{
  drawPaddle(0, tapePy0[f]);
  drawPaddle(courtWidth - paddleWidth, tapePy1[f]);

  //-- Draw court --
  u8g.drawHLine(0, 0, courtWidth);
  u8g.drawHLine(0, courtHeight - 1, courtWidth);

  // Draw Ball --
  u8g.drawBox(tapeX[f], tapeY[f], ballWidth, ballHeight);
  Serial.print("tapeX[f]=");
  Serial.println(tapeX[f]);

}

void InstantReplay()
{
  Serial.println("InstantReplay");
  Serial.print("tapePos=");
  Serial.println(tapePos);

  for (int f = tapePos; f < tapeMax; f++) {
    
  u8g.firstPage();
  do {
      DrawFrame(f);
    } while (u8g.nextPage());
    delay(500);
  }

  for (int f = 0; f < tapePos; f++) {
  
  u8g.firstPage();
  do {
      DrawFrame(f);
    } while (u8g.nextPage());
    delay(500);
  }

  state = 0;
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    if (state == 0) waitStart();
    if (state == 1) draw();
    if (state == 2) InstantReplay();
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  //delay(50);
}

