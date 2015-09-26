/*
 *  Handwritten clock
 *  by Hari Wiguna, 2015
 *  https://hackaday.io/hari
 *  www.youtube.com/user/hwiguna

v01 - Digits can draw

  Thanks to Gearbest.com for providing the matrix
  http://www.gearbest.com/development-boards/pp_65373.html
*/

// myMatrix library Copyright (c) 2015 Silviu - www.openhardware.ro
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

byte digitColor = green;

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

void setup ()
{
  myMatrix.Init(Red_Pin, Green_Pin, CLK_Pin, RowA_Pin, RowB_Pin, RowC_Pin, RowD_Pin, OE_Pin, STB_Pin);
}

void loop()
{
  //Count();
  SampleClockFace();
}

void SampleClockFace()
{
  //-- Draw frame --
  myMatrix.clearScreen();
  myMatrix.drawHLine(0, 31, 0, green);
  myMatrix.drawHLine(0, 31, 1, green);
  myMatrix.drawHLine(0, 31, 14, green);
  myMatrix.drawHLine(0, 31, 15, green);

  byte y0 = 3;
  DrawDigit(0 * 8 - 1, y0, 1);
  DrawDigit(1 * 8 - 1, y0, 0);
  DrawDigit(2 * 8 + 1, y0, 2);
  DrawDigit(3 * 8 + 1, y0, 4);

  BlinkColon();
}

void BlinkColon()
{
  for (byte i = 0; i < 6; i++)
  {
    //-- colon --
    myMatrix.drawVLine(15, 6, 7, green);
    myMatrix.drawVLine(15, 9, 10, green);
    delay(500);
    //-- colon --
    myMatrix.drawVLine(15, 6, 7, black);
    myMatrix.drawVLine(15, 9, 10, black);
    delay(500);
  }
}

void Count()
{
  //-- Count from zero to nine --
  for (int n = 0; n < 10; n++)
  {
    //-- Draw frame --
    myMatrix.clearScreen();
    myMatrix.drawHLine(0, 31, 0, green);
    myMatrix.drawHLine(0, 31, 1, green);
    myMatrix.drawHLine(0, 31, 14, green);
    myMatrix.drawHLine(0, 31, 15, green);

    //-- Draw four digits --
    for (int d = 0; d < 4; d++)
    {
      byte x0 = d * 8;
      byte y0 = 3;
      DrawDigit(x0, y0, n);
    }
    delay(500);
  }
}

void DrawDigit(byte x0, byte y0, byte n)
{
  switch (n)
  {
    case 0: DrawDigit(x0, y0, zero, sizeof(zero)); break;
    case 1: DrawDigit(x0, y0, one, sizeof(one)); break;
    case 2: DrawDigit(x0, y0, two, sizeof(two)); break;
    case 3: DrawDigit(x0, y0, three, sizeof(three)); break;
    case 4: DrawDigit(x0, y0, four, sizeof(four)); break;
    case 5: DrawDigit(x0, y0, five, sizeof(five)); break;
    case 6: DrawDigit(x0, y0, six, sizeof(six)); break;
    case 7: DrawDigit(x0, y0, seven, sizeof(seven)); break;
    case 8: DrawDigit(x0, y0, eight, sizeof(eight)); break;
    case 9: DrawDigit(x0, y0, nine, sizeof(nine)); break;
  }
}
void DrawDigit(byte x0, byte y0, byte dots[][2], byte siz)
{
  for (int i = 0; i < siz / 2; i++)
  {
    myMatrix.setPixel(x0 + dots[i][0], y0 + dots[i][1], digitColor);
    myMatrix.setPixel(x0 + dots[i][0] + 1, y0 + dots[i][1], digitColor);
    delay(50);
  }
}
