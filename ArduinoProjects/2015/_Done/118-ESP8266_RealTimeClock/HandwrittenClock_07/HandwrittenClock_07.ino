/*
 *  Handwritten clock
 *  by Hari Wiguna, 2015
 *  https://hackaday.io/hari
 *  www.youtube.com/user/hwiguna

v01 - Digits can draw
v02 - Implement eraser
v03 - Count (fake clock)
v04 - undraw instead of erase
v05 - Turn it into a slave (listen to serial port for commands from ESP)
v06 - punted on having ESP as master, now Arduino is master requesting time from ESP
v07 - Seconds as progress bar

  Thanks to Gearbest.com for providing the matrix
  http://goo.gl/1fj38d
*/

// myMatrix library Copyright (c) 2015 Silviu - http://openhardware.ro/mymatrix
#include "myMATRIX.h"

// Wiring for 16x32 Red Green LED Matrix Panel
#define RowA_Pin 2
#define RowB_Pin 3
#define RowC_Pin 4
#define RowD_Pin 5
#define OE_Pin 6
#define Red_Pin 7
#define Green_Pin 8
#define CLK_Pin 9
#define STB_Pin 10

byte digitColor = yellow;
byte drawSpeed = 30; // Smaller = faster
byte eraseSpeed = drawSpeed; // Smaller = faster

// Thanks to my awesome wife for helping me enter these coordinates!
byte zero[][2] = {{2, 0}, {3, 0}, {4, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {4, 8}, {3, 9}, {2, 9}, {1, 8}, {0, 7}, {0, 6}, {0, 5}, {0, 4}, {0, 3}, {0, 2}, {1, 1}};
byte one[][2] = {{1, 2}, {2, 1}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}};
byte two[][2] = {{0, 2}, {0, 1}, {1, 0}, {3, 0}, {4, 0}, {5, 1}, {5, 2}, {5, 3}, {4, 4}, {3, 5}, {2, 6}, {1, 7}, {0, 8}, {0, 9}, {2, 9}, {4, 9}, {5, 9}};
byte three[][2] = {{0, 0}, {2, 0}, {4, 0}, {5, 0}, {5, 1}, {4, 2}, {3, 3}, {2, 4}, {4, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {4, 9}, {2, 9}, {3, 9}, {1, 8}};
byte four[][2] = {{4, 0}, {3, 1}, {2, 2}, {1, 3}, {0, 4}, {0, 5}, {0, 6}, {2, 6}, {4, 6}, {5, 6}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}};
byte five[][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 3}, {4, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {4, 9}, {2, 9}, {1, 9}, {1, 8}, {0, 0}, {2, 0}, {4, 0}, {5, 0}};
byte six[][2] = {{4, 0}, {2, 0}, {1, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {1, 8}, {1, 9}, {3, 9}, {4, 9}, {5, 8}, {5, 7}, {5, 6}, {5, 5}, {4, 4}, {2, 4}, {1, 5}};
byte seven[][2] = {{0, 0}, {2, 0}, {4, 0}, {5, 0}, {5, 1}, {5, 2}, {4, 3}, {3, 4}, {3, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9}};
byte eight[][2] = {{3, 0}, {4, 0}, {5, 1}, {5, 2}, {5, 3}, {4, 4}, {2, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {1, 9}, {3, 9}, {4, 9}, {5, 8}, {5, 7}, {5, 6}, {5, 5}, {4, 4}, {1, 4}, {0, 3}, {0, 2}, {0, 1}, {1, 0}};
byte nine[][2] = {{4, 4}, {3, 5}, {1, 5}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {1, 0}, {3, 0}, {4, 0}, {4, 1}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {4, 8}, {3, 9}, {1, 9}};
int16_t eraser[][2] = {{ -1, 0}, {1, -1}, {5, -1}, {3, 0}, {1, 1}, { -1, 2}, { -1, 4}, {1, 3}, {3, 2}, {5, 1}, {5, 3}, {3, 4}, {1, 5}, { -1, 6}, { -1, 8}, {1, 7}, {3, 6}, {5, 5}, {5, 7}, {3, 8}, {1, 9}, {5, 9}};

byte hh = 0;
byte mm = 0;
byte ss = 0;
byte phh = 99; // Force all digits to be drawn the first time we get actual time.
byte pmm = 99;
byte pss = 99;

int refreshEveryXmillis = 250; // Make sure this is enough time to do UpdateSecondsProgress()
unsigned long timeToRefresh;

// Progress bars to indicate seconds
int halfSec = 0;
unsigned long timeForProgress;

char line[80] = "";

void setup ()
{
  myMatrix.Init(Red_Pin, Green_Pin, CLK_Pin, RowA_Pin, RowB_Pin, RowC_Pin, RowD_Pin, OE_Pin, STB_Pin);

  //-- Draw frame --
  myMatrix.clearScreen();
  //  myMatrix.drawHLine(0, 31, 0, green);
  //  myMatrix.drawHLine(0, 31, 1, green);
  //  myMatrix.drawHLine(0, 31, 14, green);
  //  myMatrix.drawHLine(0, 31, 15, green);

  Serial.begin(19200);
}

void loop()
{
  if (millis() > timeToRefresh)
  {
    Serial.println("?"); // Ask ESP, what time is it?
    timeToRefresh = millis() + refreshEveryXmillis;
  }

  // Don't know when ESP going to reply, so keep checking
  ListenForResponseFromESP();

  UpdateSecondsProgress();
}

void UpdateSecondsProgress()
{
  if (millis() > timeForProgress)
  {
    timeForProgress = millis() + 1000;
    
    byte xm = (ss + 1) / 4;
    if (xm<3) xm=3; // Small effect looks terrible, so fake them out for small seconds.
    for (byte x = 0; x <= xm; x++)
    {
      myMatrix.drawHLine(15 - x, 16 + x, 1, green);
      myMatrix.drawHLine(15 - x, 16 + x, 14, green);
      delay(150 / (xm + 1));
    }

    for (byte x = xm; x > 0; x--)
    {
      myMatrix.drawHLine(0, 16 - x, 1, black);
      myMatrix.drawHLine(15 + x, 31, 1, black);
      myMatrix.drawHLine(0, 16 - x, 14, black);
      myMatrix.drawHLine(15 + x, 31, 14, black);
      delay(150 / (xm + 1));
    }
  }
}
void UpdateSecondsProgress_1()
{
  if (ss == 0 || ss < pss) { // Erase when we start seconds over
    myMatrix.fillRectangle(0, 0, 31, 1, black);
    myMatrix.fillRectangle(0, 14, 31, 15, black);
  }
  else
  {
    byte row = ss / 15; // All four rows is 60 seconds, so a fourth of that is 15
    byte xm = ss % 15;
    byte y = 0;
    switch (row)
    {
      case 0: y = 0; break;
      case 1: y = 1; break;
      case 2: y = 14; break;
      case 3: y = 15; break;
    }
    for (byte x = 0; x <= xm; x++)
    {
      myMatrix.drawHLine(15 - x, 16 + x, y, green);
      delay(100 / (xm + 1));
    }

    for (byte x = xm; x > 0; x--)
    {
      myMatrix.drawHLine(15 - x, 16 + x, y, black);
      delay(100 / (xm + 1));
    }
  }
}


void UpdateSecondsProgress_0()
{
  if (ss == 0 || ss < pss) { // Erase when we start seconds over
    myMatrix.fillRectangle(0, 0, 31, 1, black);
    myMatrix.fillRectangle(0, 14, 31, 15, black);
  }
  else
  {
    byte row = ss / 15; // All four rows is 60 seconds, so a fourth of that is 15
    byte x = ss % 15;
    byte y = 0;
    switch (row)
    {
      case 0: y = 0; break;
      case 1: y = 1; break;
      case 2: y = 14; break;
      case 3: y = 15; break;
    }
    myMatrix.drawHLine(15 - x, 16 + x, y, green);
  }
}

void ListenForResponseFromESP()
{
  if (Serial.available() > 0) {
    int len = strlen(line);
    int inByte = Serial.read();
    if (inByte != 10) { // NOT Linefeed
      if (inByte != 13) { // NOT Carriage Return
        line[ len ] = inByte; // Collect it.
        line[ len + 1 ] = 0x00;
      }
    }
    else
    { // It *IS* linefeed! We got a line collected, process it.
      char cmd[80];
      strcpy(cmd, line);
      line[0] = 0x00;
      if ( strlen(cmd) > 0 && cmd[0] == '#' ) {
        hh = toByte(cmd, 1);
        mm = toByte(cmd, 3);
        ss = toByte(cmd, 5);
        if (hh != phh || mm != pmm || ss != pss) {
          DrawTime();
          phh = hh;
          pmm = mm;
          pss = ss;
        }
      }
      else {
        //myMatrix.clearScreen();
        //myMatrix.printString(0, 0, yellow, black, line);
      }
    }
  }
}

byte toByte(char *str, byte pos)
{
  char buf[3];
  strncpy(buf, str + pos, 2);
  buf[2] = 0;
  return atoi(buf);
}

void DrawTime()
{
  byte y0 = 3;

  //DrawColon( ss%2==0 ? digitColor : black);
  DrawColon(digitColor);
  //UpdateSecondsProgress();

  //sprintf(line, "%02d", ss);
  //myMatrix.printString(15, 9, yellow, black, line);

  if (phh / 10 != hh / 10 && phh / 10 > 0) DrawDigit(0 * 8 - 1, y0, phh / 10, black);
  if (phh % 10 != hh % 10) DrawDigit(1 * 8 - 1, y0, phh % 10, black);
  if (pmm / 10 != mm / 10) DrawDigit(2 * 8 + 1, y0, pmm / 10, black);
  if (pmm % 10 != mm % 10) DrawDigit(3 * 8 + 1, y0, pmm % 10, black);

  if ((hh / 10) > 0) DrawDigit(0 * 8 - 1, y0, hh / 10, digitColor);
  if (phh % 10 != hh % 10) DrawDigit(1 * 8 - 1, y0, hh % 10, digitColor);
  if (pmm / 10 != mm / 10) DrawDigit(2 * 8 + 1, y0, mm / 10, digitColor);
  if (pmm % 10 != mm % 10) DrawDigit(3 * 8 + 1, y0, mm % 10, digitColor);

  //DrawColon(black);
}

void Eraser(byte x0, byte y0)
{
  for (int i = 0; i < sizeof(eraser) / 4; i++)
  {
    int16_t x1 = eraser[i][0];
    int16_t y1 = eraser[i][1];
    int16_t x2 = x1 + 1;
    int16_t y2 = y1 + 1;
    if (x1 < 0) x1 = 0; if (x1 > 6) x1 = 6;
    if (x2 < 0) x2 = 0; if (x2 > 6) x2 = 6;
    if (y1 < 0) y1 = 0; if (y1 > 9) y1 = 9;
    if (y2 < 0) y2 = 0; if (y2 > 9) y2 = 9;
    myMatrix.fillRectangle(x0 + x1, y0 + y1, x0 + x2, y0 + y2, red);
    delay(eraseSpeed);
    myMatrix.fillRectangle(x0 + x1, y0 + y1, x0 + x2, y0 + y2, black);
  }
}

void BlinkColon()
{
  for (byte i = 0; i < 2; i++)
  {
    DrawColon(black);
    delay(500);
    DrawColon(yellow);
    delay(500);
  }
}

void DrawColon(byte color)
{
  myMatrix.drawVLine(15, 6, 7, color);
  myMatrix.drawVLine(15, 9, 10, color);
}

void DrawDigit(byte x0, byte y0, byte n, byte color)
{
  switch (n)
  {
    case 0: DrawDigit(x0, y0, zero, sizeof(zero), color); break;
    case 1: DrawDigit(x0, y0, one, sizeof(one), color); break;
    case 2: DrawDigit(x0, y0, two, sizeof(two), color); break;
    case 3: DrawDigit(x0, y0, three, sizeof(three), color); break;
    case 4: DrawDigit(x0, y0, four, sizeof(four), color); break;
    case 5: DrawDigit(x0, y0, five, sizeof(five), color); break;
    case 6: DrawDigit(x0, y0, six, sizeof(six), color); break;
    case 7: DrawDigit(x0, y0, seven, sizeof(seven), color); break;
    case 8: DrawDigit(x0, y0, eight, sizeof(eight), color); break;
    case 9: DrawDigit(x0, y0, nine, sizeof(nine), color); break;
  }
}

void DrawDigit(byte x0, byte y0, byte dots[][2], byte siz, byte color)
{
  for (int i = 0; i < siz / 2; i++)
  {
    myMatrix.setPixel(x0 + dots[i][0], y0 + dots[i][1], color);
    myMatrix.setPixel(x0 + dots[i][0] + 1, y0 + dots[i][1], color);
    delay(drawSpeed);
  }
}
