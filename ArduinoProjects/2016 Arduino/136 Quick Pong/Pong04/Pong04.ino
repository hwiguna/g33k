// Arduino Pong
// Hari Wiguna, 2016

// v2 - instant replay

#include "U8glib.h"

//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0/DataCommand = 9, Reset = 8
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10);    // SPI Com: SCK = 13, MOSI = 11, CS = 9, A0/DataCommand = 8, Reset = 10

//== Pong variables ==
u8g_uint_t x;
u8g_uint_t y;
u8g_uint_t dx = -1;
u8g_uint_t dy = 1;
u8g_uint_t ballWidth = 4;
u8g_uint_t ballHeight = 4;
u8g_uint_t animationSpeed = 40; //25;
u8g_uint_t paddleWidth = 2;
u8g_uint_t paddleHeight = ballHeight * 3;
u8g_uint_t py0;
u8g_uint_t py1;
u8g_uint_t courtWidth;
u8g_uint_t courtHeight;
byte p0Pin = A1;
byte p1Pin = A0;

unsigned long timeToMove = 0;
const int tapeMax = 40;
int tapePos = 0; // Index to the last recorded element
int f = 0;
u8g_uint_t tapePy0[tapeMax];
u8g_uint_t tapePy1[tapeMax];
u8g_uint_t tapeX[tapeMax];
u8g_uint_t tapeY[tapeMax];
int instantReplaySpeed = 100;
int messageSpeed = 1000;

#define STATE_RESET 0
#define STATE_IN_GAME 4
byte state = STATE_RESET;

void drawPaddle(u8g_uint_t x, u8g_uint_t y)
{
  u8g.drawBox(x, y, paddleWidth, paddleHeight);
}

bool hitsPaddle(u8g_uint_t py)
{
  return (y > py) && ( y <= (py + paddleHeight));
}

void PlayGame() {
  py0 = map( analogRead(p0Pin), 0, 1023, 0, u8g.getHeight() - paddleHeight);
  drawPaddle(0, py0);

  py1 = map( analogRead(p1Pin), 0, 1023, 0, u8g.getHeight() - paddleHeight);
  drawPaddle(courtWidth - paddleWidth, py1);

  //-- Draw court --
  u8g.drawHLine(0, 0, courtWidth);
  u8g.drawHLine(0, courtHeight - 1, courtWidth);

byte dash = 3;
  for (byte y=0; y<(courtHeight/dash/2); y++)
  {
  u8g.drawVLine(courtWidth/2, 2 + y*dash*2, dash);
  }
  
  //-- Draw Ball --
  u8g.drawBox(x, y, ballWidth, ballHeight);

  if (millis() > timeToMove) {
    x = x + dx;
    u8g_int_t prevDx = dx;
    u8g_int_t prevDy = dy;
    if (x <= 0)
      if (hitsPaddle(py0)) {
        dx = -dx;
        Beep();
      }
      else
        state = STATE_RESET;

    if ((x + ballWidth) >= courtWidth)
      if (hitsPaddle(py1)) {
        dx = -dx;
        Beep();
      }
      else
        state = STATE_RESET;

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

void waitStart()
{
  dx = 0;
  dy = 0;
  x = -ballWidth;
  y = 0;
  if (analogRead(0) == -1) {
    state = 1;
    x = courtWidth / 2;
    y = courtHeight / 2;
    dx = 1;
    dy = 1;
  }

  u8g.setContrast(analogRead(0));
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
  Serial.println("start");

  state = STATE_RESET;
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



void DisplayMessage(char* message)
{
  u8g.setFont(u8g_font_osb21);
  u8g.setFontPosCenter(); // vertical alignment
  u8g.drawStr( (courtWidth - u8g.getStrWidth(message)) / 2, courtHeight / 2, message);

  if (millis() > timeToMove) {
    state++;
    timeToMove = millis() + messageSpeed;
  }
}

void PauseThenReset()
{
  if (millis() > timeToMove) {
    state = STATE_RESET;
    timeToMove = millis() + messageSpeed;
  }
}

void Reset()
{
  x = courtWidth / 2;
  y = courtHeight / 2;
  dx = -dx;
  dy = -dy;
  if (millis() > timeToMove) {
    state = STATE_IN_GAME;
    timeToMove = millis() + messageSpeed;
  }
}

void loop(void) {
  u8g.firstPage();

  do {
    if (state == STATE_RESET ) Reset();
    //    if (state == STATE_GET_READY ) DisplayMessage("Ready");
    //    if (state == STATE_GET_SET ) DisplayMessage("Set");
    //    if (state == STATE_GET_GO ) DisplayMessage("Go!");
    if (state == STATE_IN_GAME) PlayGame();
    //    if (state == STATE_END_OF_ROUND) DisplayMessage("Replay");
    //    if (state == STATE_INSTANT_REPLAY) InstantReplay();
    //    if (state == STATE_PAUSE) PauseThenReset();
  } while ( u8g.nextPage() );

}

