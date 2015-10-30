//
// Happy Halloween
// by Hari Wiguna 2015
//
// 01 - modify to work with Chinese knockoff
// 02 - Draw Happy Halloween & Pumpkin Face
// 03 - Attempt for more face variety

// Wiring:
// Arduino A4 --> OLED SDA
// Arduino A5 --> OLED SCL
// Arduino D2 --> OLED VCC
// Arduino Gnd--> OLED Gnd
//
// Potentiometers are on Gnd and +5V, wipers go to A0, A2, A2

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

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

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int prevEyeSize = -1;
int prevEyeRotation = 0;
int prevEyeSlant = 0;
int prevMouthWidth = -1;
int eyeSep = 5;
int headR = 50;
unsigned long timeToAnimate;
unsigned long animationSpeed = 100;
int eyeSize = 10;
int eyeRotationOffset = -2;
int eyeRotation = 0;
int eyeSlant = 0;
int mouthWidth = 25;
int mouthWidthOffset = 2;
int grinHeight;
int prevGrinHeight;

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

void setup()   {
  // This is a hack to get my Chinese OLED to work.
  // I power the OLED using D2 because my OLED does not have a reset pin.
  // Without this hack, my oled displays static random dots.
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
}

void loop() {
  eyeSize = 12; //map(analogRead(A0), 0, 1023, 0, display.height() / 2);
  eyeRotation = map(analogRead(A0), 0, 1023, 0, 360);
  int eyeSlant = map(analogRead(A1), 0, 1023, 0, 90);
  int grinHeight = map(analogRead(A2), 0, 1023, +10, -15);

  if (eyeSize != prevEyeSize || eyeRotation != prevEyeRotation || eyeSlant != prevEyeSlant || mouthWidth != prevMouthWidth || grinHeight != prevGrinHeight)
  {
    display.clearDisplay();

    display.setTextColor(WHITE);
    display.setCursor(8, 0);
    display.setTextSize(2);
    display.println("Halloween!");

    //-- Head --
    display.drawCircle(display.width() / 2, display.height() / 2, headR, WHITE);

    //-- Eyes --
    DrawEyes(display.width() / 2, display.height() / 2 - 4, eyeSize, eyeRotation, eyeSlant, WHITE);

    //-- Mouth --
    DrawMouth2(mouthWidth, grinHeight, WHITE);

    display.display();

    prevEyeSize = eyeSize;
    prevEyeRotation = eyeRotation;
    prevEyeSlant = eyeSlant;
    prevMouthWidth = mouthWidth;
    prevGrinHeight = grinHeight;
  }

  if (millis() > timeToAnimate)
  {
    AnimateEyeSize();
    //AnimateEyeRotation();
    //AnimateMouth();
    timeToAnimate = millis() + animationSpeed;
  }
}

void AnimateEyeRotation()
{
  eyeRotation += eyeRotationOffset;
  if (eyeRotation > 360) eyeRotationOffset = -16;
  if (eyeRotation < 0)  eyeRotationOffset = +16;
}

void AnimateEyeSize()
{
  eyeSize += eyeRotationOffset;
  if (eyeSize > 20) eyeRotationOffset = -2;
  if (eyeSize < 4)  eyeRotationOffset = +2;
}

void AnimateMouth()
{
  mouthWidth += mouthWidthOffset;
  if (mouthWidth > 40) mouthWidthOffset = -4;
  if (mouthWidth < 3)  mouthWidthOffset = +4;
}

void DrawEyes(int x0, int y0, int r, int rotation, int slant, int color)
{
  float s[3], c[3];
  for (int i = 0; i < 3; i++)
  {
    float angle = (rotation * 2 * PI / 360) + i * 2 * PI / 3;
    if (i == 0)
      angle += (slant * 2 * PI/360);
    s[i] = sin(angle) * r;
    c[i] = cos(angle) * r;
  }

  int leftEyeX0 = x0 - (prevEyeSize + eyeSep);
  display.drawTriangle(
    leftEyeX0 - s[0], y0 + c[0],
    leftEyeX0 - s[1], y0 + c[1],
    leftEyeX0 - s[2], y0 + c[2],
    color);

  int rightEyeX0 = x0 + prevEyeSize + eyeSep;
  display.drawTriangle(
    rightEyeX0 + s[0], y0 + c[0],
    rightEyeX0 + s[1], y0 + c[1],
    rightEyeX0 + s[2], y0 + c[2],
    color);
}

void DrawMouth1(byte width, byte grinHeight, int color)
{
  int xOrigin =  display.width() / 2;
  //display.drawLine( xOrigin - width, 61, xOrigin + width, 61, color);

  int eighth = width / 4;
  int x0 = xOrigin - width;
  int x1 = xOrigin - width + eighth;
  int x2 = xOrigin - width + eighth + eighth;
  int x3 = xOrigin - width + eighth + eighth + eighth;
  int x4 = xOrigin;
  int x5 = xOrigin + width - eighth - eighth - eighth;
  int x6 = xOrigin + width - eighth - eighth;
  int x7 = xOrigin + width - eighth;
  int x8 = xOrigin + width;

  int y0 = 55;
  int y1 = 63;
  display.drawLine( x0, y0 + grinHeight, x1, y1, color);
  display.drawLine( x1, y1, x2, y0, color);
  display.drawLine( x2, y0, x3, y1, color);
  display.drawLine( x3, y1, x4, y0, color);
  display.drawLine( x4, y0, x5, y1, color);
  display.drawLine( x5, y1, x6, y0, color);
  display.drawLine( x6, y0, x7, y1, color);
  display.drawLine( x7, y1, x8, y0 + grinHeight, color);
}

void DrawMouth2(byte width, int grinHeight, int color)
{
  /*
    / B --- C \
   A           D
    \ F --- E /
   */
  int baseWidth = 10;
  int xOrigin =  display.width() / 2;
  int aX = xOrigin - width;
  int bX = xOrigin - baseWidth;
  int cX = xOrigin + baseWidth;
  int dX = xOrigin + width;
  int eX = cX;
  int fX = bX;

  int y0 = 50;
  int y1 = 55;
  int aY = y0 + grinHeight;
  int bY = y0;
  int cY = y0;
  int dY = aY;
  int eY = y1;
  int fY = eY;

  display.drawLine( aX, aY, bX, bY, color);
  display.drawLine( bX, bY, cX, cY, color);
  display.drawLine( cX, cY, dX, dY, color);
  display.drawLine( dX, dY, eX, eY, color);
  display.drawLine( eX, eY, fX, fY, color);
  display.drawLine( fX, fY, aX, aY, color);
}
