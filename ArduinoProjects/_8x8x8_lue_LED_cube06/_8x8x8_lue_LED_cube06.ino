#include <MsTimer2.h>

// 8x8x8x Blue LED Cube
// by Hari Wiguna 2014
//
// v03 - blinks all 512
// v04 - more test patterns.  Uses TimerOne library.
// v06 - Using MsTimer2

//-- Shift Register pins --
int latchPin = 13;
int clockPin = 12;
int dataPin  = 11;

//-- Globals --
volatile int8_t cube[8][8]; // byte bits = X, 1st index=Y, 2nd index = Z
volatile int8_t gZ = 0;

void SetupPins()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i=0; i<8; i++) {
    pinMode(2+i, OUTPUT);
  }
}

void setup(void) {
  SetupPins();
  CubeAllOff();
  RunTests();
  SetupTimer();
}

void SetupTimer()
{
  MsTimer2::set(8,Refresh); // was 2
  MsTimer2::start();
}

void RunTests()
{
  Serial.begin(9600);

  Serial.print("TestCubeAllOff = ");
  Serial.println(TestCubeAllOff());

  Serial.print("TestRefresh = ");
  Serial.println(TestRefresh());    // 8052 micro seconds

  Serial.end();
}

long TestCubeAllOff()
{
  long start = micros();
  CubeAllOff();
  long finish = micros();
  return finish-start;
}

long TestRefresh()
{
  long start = micros();
  Refresh();
  long finish = micros();
  return finish-start;
}

void TestPattern3()
{
  CubeAllOff();
  delay(500);
  CubeAllOn();
  delay(500);
}

void loop(void) {
  //noInterrupts();  
  //CubeAllOn();  
  //interrupts();
  //delay(100);

  //CubeAllOff();  delay(100);
  //CubeUp();
  //CubeLeftRight();
  //TestPattern1();
  //TestPattern2_Scan_one_layer();
  //TestPattern4_Scan_one_wall();
  TestPattern5_swipe_wall_up();
  //CubeAllOn(); delay(1000);
}

void Refresh(void) // WITHOUT the added delayMicroseconds, this routine takes 8052 microseconds
{
  noInterrupts();

  //-- Turn off previous layer --
  digitalWrite(2+gZ,LOW); // Turn off prev layer

  //-- Compute new layer --
  gZ++; 
  if (gZ>=8) gZ=0;

  // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
  digitalWrite(latchPin, LOW);

  //-- Spit out the bits --
  DrawLayer(gZ);

  // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
  digitalWrite(latchPin, HIGH);

  //-- Turn on this layer --
  digitalWrite(2+gZ,HIGH); // Turn on this layer

  interrupts();
}

void TurnOnLayer(int8_t z)
{
  int8_t prev = z==0 ? 7 : z-1;

  // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
  digitalWrite(latchPin, LOW);

  //-- Spit out the bits --
  DrawLayer(z);

  //-- Turn off previous layer --
  digitalWrite(2+prev,LOW); // Turn off prev layer
}

void TurnOffLayer(int8_t z)
{
  // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
  digitalWrite(latchPin, HIGH);

  //-- Turn on this layer --
  digitalWrite(2+z,HIGH); // Turn on this layer
}

void DrawLayer(int8_t z)
{
  // Spit out all 64 bits for the layer.
  for (int8_t y=0; y<8; y++) {
    shiftOut(dataPin, clockPin, MSBFIRST, cube[y][z]); // Push Most significant BYTE first   
  }  
}

void CubeAllOn()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z, 0xFF);
  }  
}

void CubeAllOff()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z, 0x00);
  }  
}

void CubeUp()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z, 0xFF);
    delay(50);
    SetLayer(z, 0x00);
  }  
}

void CubeLeftRight()
{
  for (int8_t x=0; x<8; x++) {
    SetXPlane(x);
    delay(20);
    CubeAllOff();
  }  
}

void SetXPlane(int8_t x)
{
  x = Wrap(x);
  int8_t xPattern = 1 << x;
  for (int8_t z=0; z<8; z++) {
    for (int8_t y=0; y<8; y++) {
      cube[y][z] = xPattern;
    }
  }
}

void TestPattern1()
{
  //int8_t y = 7;
  for (int8_t x=0; x<8; x++) {
    for (int8_t y=0; y<8; y++) {
      SetDot(x,y,0); 
      SetDot(7-x,y,1);
    }

    delay(20);

    for (int8_t y=0; y<8; y++) {
      ClearDot(x,y,0); 
      ClearDot(7-x,y,1);
    }
  }
}

void TestPattern2_Scan_one_layer()
{
  for (int8_t y=0; y<8; y++) {
    for (int8_t x=7; x>=0; x--) {
      SetDot(x,y,0);
      delay(64);
      ClearDot(x,y,0);
    }
  }
}

void TestPattern4_Scan_one_wall()
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=7; x>=0; x--) {
      SetDot(x,7,z);
      delay(64);
      ClearDot(x,7,z);
    }
  }
}

void TestPattern5_swipe_wall_up()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z,0xFF);
    //for (int8_t x=0; x<8; x++) SetDot(x,7,z);
    //for (int8_t y=3; y<8; y++) for (int8_t x=0; x<8; x++) SetDot(x,y,z);
    delay(64);
    SetLayer(z,0x00);
    //for (int8_t x=0; x<8; x++) ClearDot(x,7,z);
    //for (int8_t y=3; y<8; y++) for (int8_t x=0; x<8; x++) ClearDot(x,y,z);
  }
}


void SetDot(int8_t x,int8_t y,int8_t z)
{
  bitSet(cube[y][z], x);
}

void ClearDot(int8_t x,int8_t y,int8_t z)
{
  bitClear(cube[y][z], x);
}

void SetLayer(int8_t z, int8_t xByte)
{
  //z = Wrap(z);
  for (int8_t y=7; y<8; y++) {
    cube[y][z] = xByte;
    //for (int8_t x=0; x<8; x++) {
    //  if (xByte==0) ClearDot(x,y,z); else SetDot(x,y,z);
    //}
  }
}

int8_t Wrap(int8_t val)
{
  if (val>7)
    return 0;
  else if (val<0)
    return 7;
  else
    return val;
}


