// 8x8x8x Blue LED Cube
// by Hari Wiguna 2014
//
// v03 - blinks all 512
// v04 - marquee pattern

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
  CubeAllOn();
  SetupInterruptRoutine();
   
//  long start = micros();
//  LoopNormal();
//  long finish = micros();
//  Serial.begin(9600);
//  Serial.println(finish-start);
//  Serial.end();
}

void loop() {
//  CubeAllOn();
//  delay(500);
//  CubeAllOff();
}

void LoopNormal()
{
  for (int8_t z=0; z<8; z++) {
    int8_t prev = z==0 ? 7 : z-1;

    // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
    digitalWrite(latchPin, LOW);

    //-- Spit out the bits --
    DrawLayer(z);

    //-- Turn off previous layer --
    digitalWrite(2+prev,LOW); // Turn off prev layer

    // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
    digitalWrite(latchPin, HIGH);
    
    //-- Turn on this layer --
    digitalWrite(2+z,HIGH); // Turn on this layer

    //delay(500);
  }
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
    delay(500);
    SetLayer(z, 0x00);
  }  
}

void SetLayer(int8_t z, byte xByte)
{
  z = Wrap(z);
  for (int8_t y=0; y<8; y++) {
    cube[y][z] = xByte;
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

void SetupInterruptRoutine() {
  cli(); // Stop interrupts

  TCCR1A = 0; // 
  TCCR1B = 0;
  TCNT1 = 0; // Counter
  
  // compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
  OCR1A = 15624; //(16*10^6) / (2000*64) - 1; // OCR0A/OCR02A can be up to 255, OCR1A up to 65535
  
  TCCR1A |= (1 << WGM12); // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // turn on bits for 64 prescaler
  
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}

ISR(TIMER0_COMPA_vect)
{
  cycles++;
  if (cycles==10) {
    cycles=0;
    LoopNormal();  
  }
}


