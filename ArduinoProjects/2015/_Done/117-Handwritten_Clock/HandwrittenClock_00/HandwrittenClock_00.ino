/*
File	: myMATRIX_Demo.pde
Version	: 1.0
Date	: 14.01.2015
Project	: myMatrix Arduino Library

The MIT License (MIT)

Copyright (c) 2015 Silviu - www.openhardware.ro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/*
  Simple demo for <myMatrix> 16x32 Red Green LED Matrix Panel .

  The circuit:
  A   connect to digital pin 2
  B   connect to digital pin 3
  C   connect to digital pin 4
  D   connect to digital pin 5
  OE  connect to digital pin 6
  R   connect to digital pin 7
  G   connect to digital pin 8
  CLK connect to digital pin 9
  STB connect to digital pin 10
  GND connect to GND
*/

#include "myMATRIX.h"

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
  myMatrix.clearScreen();
  //HariFun();
  //HelloYouTube();
  //MakeShiftLincoln();
  //Curtains();
  //TestHorzLines();
  //TestVertLines();
  //TestEachDot();
  //Flasher();
  //Eight();

  myMatrix.drawHLine(0, 31, 0, green);
  myMatrix.drawHLine(0, 31, 1, green);

  myMatrix.drawHLine(0, 31, 14, green);
  myMatrix.drawHLine(0, 31, 15, green);

  Count();

  Eraser();
}

void Count()
{
  for (int n = 0; n < 10; n++)
  {/*
    byte **dots;
    switch (n)
  {
    case 0: dots = zero; break;
    case 1: dots = one; break;
    case 2: dots = two; break;
    case 3: dots = three; break;
    case 4: dots = four; break;
    case 5: dots = five; break;
    case 6: dots = six; break;
    case 7: dots = seven; break;
    case 8: dots = eight; break;
    case 9: dots = nine; break;
  }
  */
  for (int d = 0; d < 2; d++)
    {
      byte x0 = d * 8;
      byte y0 = 3;
    DrawDigit(x0, y0, zero);
  }
}
void Eraser()
{

}

void DrawDigit(byte x0, byte y0, byte[][2] dots)
{
  for (int i = 0; i < sizeof(dots) / 2; i++)
  {
    myMatrix.setPixel(x0 + dots[i][0], y0 + dots[i][1], digitColor);
    myMatrix.setPixel(x0 + dots[i][0] + 1, y0 + dots[i][1], digitColor);
    delay(50);
  }
}

void Write7()
{
  byte dots[][2] = {{0, 0}, {2, 0}, {4, 0}, {5, 0}, {5, 1}, {5, 2}, {4, 3}, {3, 4}, {3, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9}};
  byte y0 = 3;

  for (int d = 0; d < 2; d++)
  {
    byte x0 = d * 8;
    for (int i = 0; i < sizeof(dots) / 2; i++)
    {
      myMatrix.setPixel(x0 + dots[i][0], y0 + dots[i][1], green);
      myMatrix.setPixel(x0 + dots[i][0] + 1, y0 + dots[i][1], green);
      delay(50);
    }
    delay(500);
  }
  //myMatrix.clearScreen();
}

void Eight()
{
  //== A ==
  myMatrix.drawHLine(1, 6, 1, yellow);
  myMatrix.drawHLine(2, 5, 2, yellow);

  //== B ==
  myMatrix.drawVLine(6, 2, 7, green);
  myMatrix.drawVLine(5, 3, 6, green);

  //== C ==
  myMatrix.drawVLine(6, 8, 13, yellow);
  myMatrix.drawVLine(5, 9, 12, yellow);

  //== D ==
  myMatrix.drawHLine(2, 5, 13, green);
  myMatrix.drawHLine(1, 6, 14, green);

  //== E ==
  myMatrix.drawVLine(1, 8, 14, yellow);
  myMatrix.drawVLine(2, 9, 13, yellow);

  //== G ==
  myMatrix.drawVLine(1, 2, 7, green);
  myMatrix.drawVLine(2, 3, 6, green);

  //== E ==
  //myMatrix.drawHLine(2,5, 7, yellow);
  //myMatrix.drawHLine(2,5, 8, yellow);

  delay(500);
  myMatrix.clearScreen();
  delay(500);
}

void Flasher()
{
  myMatrix.fillRectangle(0, 0, 31, 15, red);
  delay(500);
  myMatrix.clearScreen();
  delay(500);

  myMatrix.fillRectangle(0, 0, 31, 15, green);
  delay(500);
  myMatrix.clearScreen();
  delay(500);

  myMatrix.fillRectangle(0, 0, 31, 15, yellow);
  delay(500);
  myMatrix.clearScreen();
  delay(500);
}
void HariFun()
{
  // Hari
  // Fun
  // #113
  // 16x32 LED Matrix

  myMatrix.printString(5, 1, green, black, "Hari");  delay(500);
  myMatrix.printString(8, 9, green, black, "Fun");  delay(1000);
  myMatrix.clearScreen();
  myMatrix.printString(4, 4, red, black, "#");
  myMatrix.printString(11, 4, red, black, "112");
  delay(1500);
  myMatrix.hScroll(4, green, black, "    16x32 LED Matrix!     ");
}

void MakeShiftLincoln()
{
  myMatrix.hScroll(4, yellow, black, "        Welcome to      ");

  myMatrix.printString(4, 0, red, black, "Make");
  delay(500);
  myMatrix.printString(2, 8, red, black, "Shift");
  delay(1000);

  myMatrix.clearScreen();
  myMatrix.hScroll(4, red, black, "      Lincoln      ");
}

void HelloYouTube()
{
  char scrolltext_1[] = "     * Hello YouTube! *      ";
  char scrolltext_2[] = "     * Library by Silviu *      ";

  myMatrix.clearScreen();
  myMatrix.drawHLine(1, 30, 0, red);
  myMatrix.drawHLine(1, 30, 8, red);
  myMatrix.drawVLine(0, 1, 7, red);
  myMatrix.drawVLine(31, 1, 7, red);
  myMatrix.printString(5, 1, red, black, "Hari");

  myMatrix.hScroll(9, yellow, black, scrolltext_1);
  myMatrix.hScroll(9, red, black, scrolltext_2);
}

void TestEachDot()
{
  for (int r = 0; r < 16; r++)
  {
    for (int c = 0; c < 32; c++)
    {
      myMatrix.setPixel(c, r, green);
      delay(10);
      myMatrix.setPixel(c, r, black);
    }
  }
}

void Test2()
{
  for (int r = 15; r < 16; r++)
  {
    for (int c = 0; c < 32; c++)
    {
      myMatrix.setPixel(c, r, green);
      delay(100);
    }
  }


  for (int r = 15; r < 16; r++)
  {
    for (int c = 0; c < 32; c++)
    {
      myMatrix.setPixel(c, r, black);
      delay(500);
    }
  }
}

void TestVertLines()
{
  for (int i = 0; i < 32; i++)
  {
    int prev = i == 0 ? 31 : i - 1;
    myMatrix.drawVLine(prev, 0, 15, black);
    myMatrix.drawVLine(i, 0, 15, red);
    delay(300);
  }
}

void TestHorzLines()
{
  for (int i = 8; i < 16; i++)
  {
    myMatrix.drawHLine(0, 5, i, green);
    myMatrix.drawHLine(6, 9, i, green);
    delay(500);
    myMatrix.drawHLine(0, 5, i, black);
    myMatrix.drawHLine(6, 9, i, black);
  }
}


void Curtains()
{
  CurtainOpen(green);
  CurtainClose(black);
  CurtainOpen(red);
  CurtainClose(black);
  CurtainOpen(yellow);
  CurtainClose(black);
}

void CurtainOpen(int color)
{
  for (int i = 0; i < 16; i++)
  {
    myMatrix.drawVLine(15 - i, 0, 15, color);
    myMatrix.drawVLine(16 + i, 0, 15, color);
    delay(50);
  }
}


void CurtainClose(int color)
{
  for (int i = 0; i < 16; i++)
  {
    myMatrix.drawVLine(i, 0, 15, color);
    myMatrix.drawVLine(31 - i, 0, 15, color);
    delay(50);
  }
}

