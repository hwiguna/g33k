//
// Hari's LED Cube
//
// Version history:
// 01 - Tests each of the 64 LEDs one by one
// 02 - Use Simon Monk's Timer library
// 05 - Setup CPU timer registers manually for better control
// http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=50106
// 06 - Call RefreshCube from interrupt
// 07 - Explosion
// 08 - Try to flip Analog pins to input to read Accelerometer
// 09 - Cleanup for blogpost

// How it works:
// Each level of the LED cube is made of sixteen (4x4) LEDs.
// Each of the 16 LEDs anode(+) are connected to 16 dedicated OUTPUT pins on the Arduino.
// All 16 LEDs cathodes(-) are connected TOGETHER and driven by a ONE Arduino pin via a transistor.
// All levels share the same 16 anodes(+) but keep separate cathodes(-).
// The code would setup which of the 16 LEDs should be on at each level and then turn on that level.
// Do this for all levels VERY QUICKLY and it would appear that all LEDs are individually controllable.

//--- Preferences --
int velocity = 90;
int isOn = HIGH;

//--- Hardware pins ---
// 16 LED Anode(+) pins -- 4x4 LEDs per level
int leds[] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int numLeds = sizeof(leds)/sizeof(int);

// 4 LED Cathod(-) pins -- to pick which level the above 4x4 pattern is for.
int levelPins[] = {16,17,18,19};

//--- The Cube "bitmap" ---
// Since we only have 16 single color LED per layer, we can represent each layer as one 16 bit integer
int levelMap[4]; // 4 layers of 16 bits each
byte level = 0; // Used by refreshCube

//--- Animation ---
int frame = 0;
byte bitmap[4][4][4];
int acc[3]; // accelerometer values x,y,z axis.  Unfortunately I have not been able to get the accelerator to work with the cube. :-(

void setup() {
  
  //-- Setup ALL 20 Arduino I/O pins (including analog pins) as output --
  for (byte pin=0; pin < 20; pin++)
  {
    pinMode(pin, OUTPUT);     
  }
  
  ClearBitmap();

  SetupTimer();
  
  Zplane(3); CopyToDisplay();
}

void SetupTimer()
{
  cli(); // Stop global interrupt
  
  TCCR1A = 0; // Timer/Counter Control Register 1 A
  TCCR1B = 0; // Timer/Counter Control Register 1 B
  
  TCCR1B |= (1 << WGM12); // Configure Timer 1 for CTC mode
  OCR1A = 0xFF; // CTC Compare value
  TIMSK1 |= (1 << OCIE1A); // Tell CTC to call interrupt routine in addition to setting CTC flag

  // CS12  CS11  CS10  Description
  //  0     0     1    clk / 1
  //  0     1     0    clk / 8
  //  0     1     1    clk / 64
  //  1     0     0    clk / 256
  //  1     1     0    clk / 1024
  TCCR1B |= (1 << CS10); // CS10, CS11, CS12 bits control prescaler. 
  TCCR1B |= (1 << CS11); // CS10, CS11, CS12 bits control prescaler. 
  
  sei(); // enable global interrupt again
}

ISR(TIMER1_COMPA_vect)
{
  RefreshCube();
}

void ClearBitmap()
{
  for (byte x=0; x<4; x++)
    for (byte y=0; y < 4; y++)
      for (byte z=0; z < 4; z++)
        bitmap[x][y][z] = 0;
}

void loop() 
{
  Fireworks();

  Bounces();
}

void Fireworks()
{
  byte xd = 1;
  byte yd = 1;
  byte zd = 1;
  byte x = 1;
  byte y = 1;
  byte z = 1;
  
  for (int count=0; count<4; count++)
  {
    ClearBitmap();
    
    for (byte numDots=0; numDots < 8; numDots++)
    {
      x = random(4);
      y = random(4);
      z = random(4);
      
      bitmap[x][y][z] = 1;
      CopyToDisplay();
      delay(velocity*2);
    }

    for (byte count=0; count<1; count++)
      Explosion();
  }
}

void Bounces()
{
  for (byte axis=0; axis < 3; axis++)
  {
    for (byte c=0; c < 4; c++)
    {
      //-- Downward --
      for (byte a=0; a < 4; a++)
      {  
        ClearBitmap(); 
        switch (axis)
        {
          case 0: Xplane(a); break;
          case 1: Yplane(a); break;
          case 2: Zplane(a); break;
        }
        CopyToDisplay();
        delay(velocity);
      }
    
      //-- Upward --
      for (byte a=2; a > 0; a--)
      {  
        ClearBitmap(); 
        switch (axis)
        {
          case 0: Xplane(a); break;
          case 1: Yplane(a); break;
          case 2: Zplane(a); break;
        }
        CopyToDisplay();
        delay(velocity);
      }
    }
  }
}

void Explosion()
{
  //-- Nothing --
  ClearBitmap();
  CopyToDisplay();
  delay(velocity);
  
  //-- one dot in the middle --
  bitmap[1][1][1] = 1;
  CopyToDisplay();
  delay(velocity);

  //-- four dots in the middle --
  bitmap[1][2][1] = 1;
  bitmap[1][1][2] = 1;
  bitmap[2][2][2] = 1;
  CopyToDisplay();
  delay(velocity);
  
  //-- All excepts the cube corners --
  for (byte z=0; z < 4; z++)
  {
    for (byte x=1; x < 3; x++)
    {
      for (byte y=1; y < 3; y++)
      {
        bitmap[x][y][z] = 1;
      }
    }
  }
  CopyToDisplay();
  delay(velocity);

  //-- turn them all on --
  for (byte z=0; z < 4; z++)
  {
    Zplane(z);
    CopyToDisplay();
  }
  delay(velocity);
  delay(velocity);
}

void Xplane(byte x)
{
  for (byte y=0; y < 4; y++)
     for (byte z=0; z < 4; z++)
     bitmap[x][y][z] = 1;
}

void Yplane(byte y)
{
  for (byte x=0; x < 4; x++)
     for (byte z=0; z < 4; z++)
       bitmap[x][y][z] = 1;
}

void Zplane(byte z)
{
  for (byte x=0; x < 4; x++)
    for (byte y=0; y < 4; y++)
        bitmap[x][y][z] = 1;
}

void CopyToDisplay()
{
  for (byte x=0; x < 4; x++)
    for (byte y=0; y < 4; y++)
      for (byte z=0; z < 4; z++)
        if (bitmap[x][y][z])
          bitSet(levelMap[ z ], x*4 + y);
         else 
          bitClear(levelMap[ z ], x*4 + y);
}

void RefreshCube()
{
  //-- Turn off previous level before we mess with the 16 anodes --
  byte levelPin = levelPins[level];
  digitalWrite(levelPin, LOW);
  
  //-- Compute next level, but don't turn it on until we setup the 16 anodes for the new level --
  level++;
  if (level==4) level=0;
  
  //-- Setup the 16 anodes for this level --
  int thisLevel = levelMap[level];
  for (byte led=0; led < numLeds; led++)
  {
    byte ledPin = leds[led];
    byte ledState = bitRead( thisLevel, led );
    digitalWrite(ledPin, ledState);
  }

  //-- Now that the 16 anodes are set, turn on the layer (won't be turned off till next refresCube) --
  levelPin = levelPins[level];
  digitalWrite(levelPin, HIGH);
}

