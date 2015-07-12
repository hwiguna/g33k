// HariChord, 2015
// Playing with OLED Display
// Big thanks to AdaFruit for providing the wonderful libraries!

/*********************************************************************
 * This is an example for our Monochrome OLEDs based on SSD1306 drivers
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/category/63_98
 * 
 * This example is for a 128x64 size display using SPI to communicate
 * 4 or 5 pins are required to interface
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada  for Adafruit Industries.  
 * BSD license, check license.txt for more information
 * All text above, and the splash screen must be included in any redistribution
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
{ 
  B00000000, B11000000,
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
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int nFrames = 36;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
}


void loop() {
  for (int frame=0; frame < nFrames; frame++)
  {
    HariChord(frame);
  }

  for (int frame=(nFrames-1); frame >= 0; frame--)
  {
    HariChord(frame);
  }
}

void HariChord(int frame)
{
  display.clearDisplay();
  int n = 7;
  int r = frame * 64 / nFrames;
  float rot = frame * 2*PI / nFrames;
  for (int i=0; i<(n-1); i++)
  {
    float a = rot + i * 2*PI / n;
    int x1 = 64 + cos(a) * r;
    int y1 = 32 + sin(a) * r;
    for (int j=i+1; j<n; j++)
    {
      a = rot + j * 2*PI / n;
      int x2 = 64 + cos(a) * r;
      int y2 = 32 + sin(a) * r;
      display.drawLine(x1,y1, x2,y2, WHITE);
    }
  }
  display.display();
}
