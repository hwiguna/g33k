int dataPin = 2;  // SN74595 pin 14 (DS / SER)
int latchPin = 3; // SN74595 pin 12 (STCP / RCLK)
int clockPin = 4; // SN74595 pin 11 (SHCP / SRCLK)

void setup() {                
  pinMode(clockPin, OUTPUT);     
  pinMode(dataPin, OUTPUT);     
  pinMode(latchPin, OUTPUT);     

  digitalWrite(clockPin,0);
  digitalWrite(dataPin,0);
  digitalWrite(latchPin,0);

  //AllZeroes();
  //Pattern_01001000();
  
  digitalWrite(latchPin,0);
  shiftOut(dataPin, clockPin, LSBFIRST, B00010010);
  digitalWrite(latchPin,1);
}

void AllZeroes()
{
  //-- All zeroes --
  digitalWrite(latchPin,0);
  digitalWrite(dataPin,0);
  for (byte i=0; i<8; i++) {
    digitalWrite(clockPin,0);
    digitalWrite(clockPin,HIGH);
  }
  digitalWrite(latchPin,1);
}

void Pattern_01001000()
{
  //-- All zeroes --
  digitalWrite(latchPin,0);  // Don't show on output as we're shifting
  
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,1);    digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);

  digitalWrite(clockPin,0);  digitalWrite(dataPin,1);  digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);
  digitalWrite(clockPin,0);  digitalWrite(dataPin,0);  digitalWrite(clockPin,1);

  digitalWrite(latchPin,1); // Show what we've been shifting
}

void loop()
{
}

