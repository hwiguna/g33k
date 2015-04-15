// 7-Segment sketch by Hari Wiguna, 2015
// for Jay (Joseph Chrzempiec)
// v1: count up test
// v2: display time
// v3: Read the RTC (Real Time Clock) module
// v4: Use DS3231 library by Eric Ayars instead of AdaFruit's DS1307 library
// v5: Use A DIFFERENT DS3231 library by Korneliusz Jarzebski -- works with Jay's green RTC

#include <DS3231.h>
#include <Wire.h>

DS3231 clock;
RTCDateTime dt;

// Customizable options
const int numberOfDigits = 4;
const int segmentOnValue = 0; // Set to 1 if you need (+) to turn on a segment, set to 0 if you need (GND) to turn on a segment
const int readRTCRateInMs = 100; // Check RTC every 100 ms.
const bool testMode = true; // true shows MM:SS, false shows HH:MM

// To keep things simpler, I've opted to mandate that pins must be consecutive.
int segmentAPin = 2; // A=D2, B=D3, etc...
int digit0Pin = 9; // Least significant digit (right most)=D9, next digit to its left=D10, etc...

// Each array element represents the segment pattern.
// Zeroth element is pattern for the digit "0", 1st element is "1", etc.
// Most significant bit in each element is segment A, followed by segment B, etc.
// Least significant bit is unused (since we have 8 bits and only 7 segments).
//  ---A---
// |       |
// F       B
// |       |
//  ---G---
// |       |
// E       C
// |       |
//  ---D---
int segmentPatterns[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};

int digitPatterns[numberOfDigits]; // Array elements are what digits are being displayed by the LEDs

unsigned long timeToReadRTC = 0;

void setup() {
  SetupRTC();
  SetupPins();
  ReadRTC();
}

void SetupRTC()
{
  //Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif

  clock.begin();
  
  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);
}

void loop() {
  if (millis() > timeToReadRTC)
  {
    ReadRTC();
    timeToReadRTC = millis() + readRTCRateInMs;
  }
  RefreshLEDs();
}

void SetupPins()
{
  for (int i = 0; i < 7; i++)
    pinMode(segmentAPin + i, OUTPUT);

  for (int i = 0; i < numberOfDigits; i++)
    pinMode(digit0Pin + i, OUTPUT);
}

void ReadRTC()
{
  dt = clock.getDateTime();
  
  int hour = dt.hour;
  int minute = dt.minute;
  int seconds = dt.second;
  if (testMode) {
    SetDigit(0, seconds % 10);
    SetDigit(1, seconds/ 10);
    SetDigit(2, minute % 10);
    SetDigit(3, minute / 10);
  }
  else
  {
    SetDigit(0, minute % 10);
    SetDigit(1, minute/ 10);
    SetDigit(2, hour % 10);
    SetDigit(3, hour / 10);
  }
}

void SetDigit(int whichDigit, int whatToDisplay)
{
  digitPatterns[ whichDigit ] = segmentPatterns[ whatToDisplay ];
}

void RefreshLEDs()
{
  for (int digitIndex = 0; digitIndex < numberOfDigits; digitIndex++)
  {
    // Setup segments for that digit position.
    for (int segmentIndex = 0; segmentIndex < 7; segmentIndex++)
    {
      // This could have been simpler had I wired my segments so least significant bit is segment A. Oh well...
      digitalWrite( segmentAPin + segmentIndex, bitRead( digitPatterns[digitIndex], 7-segmentIndex) == segmentOnValue);
    }

    // Turn on Digit's common Anode
    digitalWrite( digit0Pin + digitIndex, HIGH);

    // Wait a little to allow humans to see
    delayMicroseconds(500);

    // Turn off Digit Anode
    digitalWrite( digit0Pin + digitIndex, LOW);
  }
}

