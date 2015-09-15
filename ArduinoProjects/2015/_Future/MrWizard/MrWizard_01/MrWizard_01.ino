// Mr. Wizard
// v00 - Design the "UI"
// v01 - Implement the wizardry

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int  prevmm;
int  prevdd;
int  prevyy;
int  mm = 9;
int  dd = 14;
int  yy = 2015;

void DisplayInputScreen(int mm, int dd, int yyyy)
{
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("Enter your");

  display.setCursor(0, 18);
  display.println("birthday..");

  display.setCursor(0, 44);
  display.print(mm);
  display.print("/");
  display.print(dd);
  display.print("/");
  display.print(yyyy);
  display.display();
}

void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  DisplayInputScreen(9, 14, 2015);
  SetupButtons();
  /*
    // draw a single pixel
    display.drawPixel(10, 10, WHITE);
    // Show the display buffer on the hardware.
    // NOTE: You _must_ call display after making any drawing commands
    // to make them visible on the display hardware!
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw many lines
    testdrawline();
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw rectangles
    testdrawrect();
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw multiple rectangles
    testfillrect();
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw mulitple circles
    testdrawcircle();
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw a white circle, 10 pixel radius
    display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
    display.display();
    delay(2000);
    display.clearDisplay();

    testdrawroundrect();
    delay(2000);
    display.clearDisplay();

    testfillroundrect();
    delay(2000);
    display.clearDisplay();

    testdrawtriangle();
    delay(2000);
    display.clearDisplay();

    testfilltriangle();
    delay(2000);
    display.clearDisplay();

    // draw the first ~12 characters in the font
    testdrawchar();
    display.display();
    delay(2000);
    display.clearDisplay();

    // draw scrolling text
    testscrolltext();
    delay(2000);
    display.clearDisplay();

    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Hello, world!");
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    display.display();
    delay(2000);

    // miniature bitmap display
    display.clearDisplay();
    display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
    display.display();

    // invert the display
    display.invertDisplay(true);
    delay(1000);
    display.invertDisplay(false);
    delay(1000);

    // draw a bitmap icon and 'animate' movement
    testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
  */

}

void SetupButtons()
{
  for (byte i = 0; i < 8; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // Setup pullup resistor
  }
  pinMode(12, INPUT);
  digitalWrite(12, HIGH); // Setup pullup resistor
}

void loop() {
  mm += (digitalRead(0) == 0);
  mm -= (digitalRead(1) == 0);
  if (mm < 1) mm = 1;
  if (mm > 12) mm = 12;

  dd += (digitalRead(2) == 0);
  dd -= (digitalRead(3) == 0);
  if (dd < 1) dd = 1;
  if (dd > 31) dd = 31;

  yy += (digitalRead(4) == 0) * 100;
  yy -= (digitalRead(5) == 0) * 100;
  yy += (digitalRead(6) == 0);
  yy -= (digitalRead(7) == 0);
  if (yy < 1800) yy = 1800;
  if (yy > 2499) yy = 2499;

  if (digitalRead(12) == 0)
    ComputeDayOfWeek();

  if (mm != prevmm || dd != prevdd || yy != prevyy)
  {
    DisplayInputScreen(mm, dd, yy);
    prevmm = mm;
    prevdd = dd;
    prevyy = yy;
    delay(200);
  }
}

void ComputeDayOfWeek()
{
  byte monthCodes[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
  byte centuryCodes[] = {2, 0, 6, 4, 2, 0, 6};
  String dows[] = {"SATURDAY", "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY"};

  int yy2 = yy % 100;
  int century = yy - yy2;
  int yearCode = ((yy2 + centuryCodes[century / 100 - 18]) % 7 + (yy2 / 4)) % 7;
  int monthCode = monthCodes[mm - 1];
  int dow = (yearCode + monthCode + dd) % 7;
  if (mm <= 2 && (yy % 4) == 0) dow--;
  if (dow < 0) dow += 7;

  display.clearDisplay();

  String fullDate = String(mm,DEC);
  fullDate += "/";
  fullDate += String(dd,DEC);
  fullDate += "/";
  fullDate += String(yy,DEC);
  display.setCursor(64 - fullDate.length() / 2*13, 0);

    display.setTextColor(WHITE);
  display.setTextSize(2);

display.println(fullDate);

  String isA = "is a";
  display.setCursor(64 - isA.length() / 2 * 12, 18);
  display.println(isA);

  display.setCursor(64 - dows[dow].length() / 2 * 12, 44);
  display.print(dows[dow]);
  display.display();
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.clearDisplay();
  display.println("scroll");
  display.display();

  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}

