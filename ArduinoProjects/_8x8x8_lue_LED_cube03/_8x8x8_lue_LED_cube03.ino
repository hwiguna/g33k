// 8x8x8x Blue LED Cube
// by Hari Wiguna 2014

//-- Shift Register pins --
int latchPin = 13;
int clockPin = 12;
int dataPin  = 11;

//-- Globals --
int cycles = 0;
byte cube[8][8]; // byte bits = X, 1st index=Y, 2nd index = Z

void SetupPins()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  for (int i=0; i<8; i++) {
    pinMode(2+i, OUTPUT);
  }
}

void setup() {
  SetupPins();
  CubeAllOff();
  //SetupInterruptRoutine();
}

void loop() {
  if (cycles==0) CubeAllOn();
  if (cycles==100) CubeAllOff();
  cycles++;
  if (cycles>200) cycles=0;

  LoopNormal();
}

void LoopNormal()
{
  for (int i=0; i<8; i++) {
    int prev = i==0 ? 7 : i-1;


    // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
    digitalWrite(latchPin, LOW);

    //-- Spit out the bits --
    DrawLayer(i);

    //-- Turn off previous layer --
    digitalWrite(2+prev,LOW); // Turn off prev layer

    // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
    digitalWrite(latchPin, HIGH);
    
    //-- Turn on this layer --
    digitalWrite(2+i,HIGH); // Turn on this layer

    //delay(500);
  }
}

void DrawLayer(byte z)
{
  // Spit out all 64 bits for the layer.
  for (byte y=0; y<8; y++) {
    shiftOut(dataPin, clockPin, MSBFIRST, cube[y][z]); // Push Most significant BYTE first   
  }  

}

void SetupPattern()
{
}

void CubeAllOn()
{
  for (byte z=0; z<8; z++) {
    for (byte y=0; y<8; y++) {
//      for (byte x=0; x<8; x++) {
//        bitSet(cube[y][z],x);
//      }
      cube[y][z] = 0xFF;
    }
  }  
}

void CubeAllOff()
{
  for (byte z=0; z<8; z++) {
    for (byte y=0; y<8; y++) {
      //for (byte x=0; x<8; x++) {
      //  bitClear(cube[y][z],x);
      //}
      cube[y][z] = 0;
    }
  }  
}

void SetupInterruptRoutine() {
  cli(); // Stop interrupts

  TCCR0A = 0; // 
  TCCR0B = 0;
  TCNT0 = 0; // Counter
  
  // compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
  OCR0A = 1; //(16*10^6) / (2000*64) - 1; // OCR0A/OCR02A can be up to 255, OCR1A up to 65535
  
  TCCR0A |= (1 << WGM01); // Turn on CTC mode
  TCCR0B |= (1 << CS01) | (1 << CS00); // turn on bits for 64 prescaler
  
  TIMSK0 |= (1 << OCIE0A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}

ISR(TIMER0_COMPA_vect)
{
  cycles++;
  if (cycles==8) cycles=0;
  RefreshCube();
  
//  if ((cycles % 5) == 0)
//    UpdateBitmap();
}


void RefreshCube()
{
  //for (int i=0; i<8; i++) {
  int i = cycles;
    int prev = i==0 ? 7 : i-1;
    digitalWrite(2+prev,LOW); // Turn off prev layer
    digitalWrite(2+i,HIGH); // Turn on this layer
    //delay(500);
    //delayMicroseconds(2200);
  //}
}

