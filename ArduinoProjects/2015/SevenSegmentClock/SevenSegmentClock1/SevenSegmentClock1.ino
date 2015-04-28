// 7-Segment sketch by Hari Wiguna, 2015
// for Jay (Joseph Chrzempiec)
// v1: count up test
// v2: display time

// Customizable options
const int numberOfDigits = 4;
const int segmentOnValue = 0; // Set to 1 if you need (+) to turn on a segment, set to 0 if you need (GND) to turn on a segment

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

//-- Test Variables --
int test = 0;
int timeToIncrement = 100;

void setup() {
  SetupPins();
  SetupAllDigits();
}

void loop() {
  if (timeToIncrement-- == 0)
  {
    test++;
    SetupAllDigits();
    timeToIncrement = 30;
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

void SetupAllDigits()
{
  SetDigit(0, test % 10);
  SetDigit(1, (test % 100) / 10);
  SetDigit(2, (test % 1000) / 100);
  SetDigit(3, test / 1000);
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

