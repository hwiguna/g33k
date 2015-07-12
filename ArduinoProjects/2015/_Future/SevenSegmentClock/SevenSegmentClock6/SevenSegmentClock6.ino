
// 7-Segment sketch by Hari Wiguna, 2015
// for Jay (Joseph Chrzempiec)
// v1: count up test
// v2: display time
// v3: Read the RTC (Real Time Clock) module
// v4: Use DS3231 library by Eric Ayars instead of AdaFruit's DS1307 library
// v5: Use A DIFFERENT DS3231 library by Korneliusz Jarzebski -- works with Jay's green RTC
// v6: Use TimerOne

#include <DS3231.h>
#include <Wire.h>
#include <TimerOne.h>

DS3231 clock;
RTCDateTime dt;

// Customizable options
const int numberOfDigits = 4;
const int segmentOnValue = 0; // Set to 1 if you need (+) to turn on a segment, set to 0 if you need (GND) to turn on a segment
const bool testMode = false; // true shows MM:SS, false shows HH:MM
const bool showAmPm = true;

// To keep things simpler, I've opted to mandate that pins must be consecutive.
int segmentAPin = 2; // A=D2, B=D3, etc...
int digit0Pin = 9; // Least significant digit (right most)=D9, next digit to its left=D10, etc...
int colonPin = 13;
int pmPin = A0;

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

unsigned long refreshRate = 1000000/70/6; // 70Hz per digit, 6 digits
unsigned long rtcRate = refreshRate / 1000; // Every thousandth time we refresh the screen, check RTC
volatile unsigned long rtcCountdown = rtcRate;
int digitIndex;

void setup() {
  Serial.begin(9600);
  SetupRTC();
  SetupPins();
  SetupTimer();
  ReadRTC();
}

void SetupTimer()
{
  Timer1.initialize(refreshRate); // in microseconds
  Timer1.attachInterrupt(TimerElapsed);
}

void SetupRTC()
{
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
  if (rtcCountdown==0)
  {
    ReadRTC();
    rtcCountdown=rtcRate;
  }
}

void SetupPins()
{
  for (int i = 0; i < 7; i++)
    pinMode(segmentAPin + i, OUTPUT);

  for (int i = 0; i < numberOfDigits; i++)
    pinMode(digit0Pin + i, OUTPUT);
    
  pinMode(colonPin, OUTPUT);
  pinMode(pmPin, OUTPUT);
}

void TimerElapsed()
{
  noInterrupts();
  RefreshLEDs();
  interrupts();
}

void ReadRTC()
{
  dt = clock.getDateTime();
  
  int hour = dt.hour;
  int minute = dt.minute;
  int seconds = dt.second;
  
  if (showAmPm)
  {
    bool isPM = hour>12;
    digitalWrite(pmPin, !isPM);
    
    if (hour==0) hour=12;
    if (hour>12) hour-=12;
  }
  
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
  
  //-- Turn on colon between HH:MM when seconds is an odd number --
  digitalWrite(colonPin, (seconds % 2));
}

void SetDigit(int whichDigit, int whatToDisplay)
{
  //Serial.print("digit=");  Serial.print(whichDigit);
  //Serial.print(" whatToDisplay=");  Serial.println(whatToDisplay);
  
  digitPatterns[ whichDigit ] = segmentPatterns[ whatToDisplay ];
}

void RefreshLEDs()
{
  // Turn Previous off Digit Anode
  digitalWrite( digit0Pin + digitIndex, LOW);

  // Find out the next digit
  if (++digitIndex == numberOfDigits) digitIndex=0;

  // Setup segments for that digit position.
  for (int segmentIndex = 0; segmentIndex < 7; segmentIndex++)
  {
    // This could have been simpler had I wired my segments so least significant bit is segment A. Oh well...
    digitalWrite( segmentAPin + segmentIndex, bitRead( digitPatterns[digitIndex], 7-segmentIndex) == segmentOnValue);
  }

  // Turn on Digit's common Anode
  digitalWrite( digit0Pin + digitIndex, HIGH);
  
  // Decrement rtc countdown.  When this reaches zero, we read the RTC
  rtcCountdown--;
}

