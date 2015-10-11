/*
File	: myMATRIXclass.h
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

// ensure this library description is only included once
#ifndef espMATRIXClass_h
#define espMATRIXClass_h

  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) \
   || defined(__AVR_ATmega644__)  || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) \
   || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega88P__)  || defined(__AVR_ATmega48P__) 
    #define newTimer2
  #endif
  #if defined(__AVR_ATmega32__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega64__)
    #define oldTimer2  
  #endif  


///#include <avr/pgmspace.h>

#if ARDUINO < 100
#include "wiring.h"
#else
#include "Arduino.h"
#endif
	
#include "font5x7.h"

#define black  0
#define green  1
#define red    2
#define yellow 3


// library interface description
class myMATRIX
{
  // user-accessible "public" interface
  public:
    volatile byte matrixBufferRed[64];   
    volatile byte matrixBufferGreen[64];  

    myMATRIX();
    void Init(uint8_t pinRed, uint8_t pinGreen, uint8_t pinClock, 
                 uint8_t pinRowA, uint8_t pinRowB, uint8_t pinRowC, uint8_t pinRowD,
                 uint8_t pinOE, uint8_t pinSTB);

    void setPixel(uint8_t x ,uint8_t y, uint8_t color);
    void fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    void drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    void clearScreen();
    void printChar(uint8_t x,uint8_t y, uint8_t For_color, uint8_t Bk_color, char ch);
    void printString(uint8_t x, uint8_t y, uint8_t For_color, uint8_t Bk_color,char *p);
    void drawVLine(uint16_t x, uint16_t y1, uint16_t y2, uint8_t color);
    void drawHLine(uint16_t x1, uint16_t x2, uint16_t y, uint8_t color);
    void hScroll(uint8_t y, uint8_t For_color, uint8_t Bk_color,char *p);
    void Show();
// library-accessible "private" interface
  private:
    byte row; 
    //volatile uint32_t *outRed;
    //volatile uint32_t *outGreen;
    //volatile uint32_t *outClock;
    //volatile uint32_t *outRowA;
    //volatile uint32_t *outRowB;
    //volatile uint32_t *outRowC;
    //volatile uint32_t *outRowD;
    //volatile uint32_t *outOE;
    //volatile uint32_t *outSTB;
    
    uint8_t bitRed;
    uint8_t bitGreen;
    uint8_t bitClock;
    uint8_t bitRowA;
    uint8_t bitRowB;
    uint8_t bitRowC;
    uint8_t bitRowD;
    uint8_t bitOE;
    uint8_t bitSTB;
   
    void t_shiftOut(uint8_t dataRed,uint8_t dataGreen);  	
    void rowScan(byte row);
    byte getPixelChar(uint8_t x, uint8_t y1, char ch);
    byte getPixelHString(uint16_t x, uint16_t y, char *p);
    void timer2Setup(void);
};

unsigned int lenString(char *p);

#endif

