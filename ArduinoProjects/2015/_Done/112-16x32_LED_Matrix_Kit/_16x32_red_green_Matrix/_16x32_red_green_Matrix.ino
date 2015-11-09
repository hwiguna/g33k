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

void setup ()
{
  myMatrix.Init(Red_Pin, Green_Pin, CLK_Pin, RowA_Pin, RowB_Pin, RowC_Pin, RowD_Pin, OE_Pin, STB_Pin);
}

void loop()
{
  myMatrix.clearScreen();
  //HariFun();
  //HelloYouTube();
  MakeShiftLincoln();
  //Curtains();
}

void HariFun()
{
  // Hari
  // Fun
  // #113
  // 16x32 LED Matrix

  myMatrix.printString(5,1, green, black, "Hari");  delay(500);
  myMatrix.printString(8,9, green, black, "Fun");  delay(1000);
  myMatrix.clearScreen();
  myMatrix.printString(4,4, red, black, "#");
  myMatrix.printString(11,4, red, black, "112");
  delay(1500);
  myMatrix.hScroll(4, yellow, black, "    16x32 LED Matrix!     ");
}

void MakeShiftLincoln()
{
  myMatrix.hScroll(4, yellow, black, "      We are...      ");

  myMatrix.printString(4,0, red, black, "Make");
  delay(500);
  myMatrix.printString(2,8, red, black, "Shift");
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

