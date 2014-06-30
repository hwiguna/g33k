//-- Ports --
int led0 = 11;
int led1 = 13;

//-- Timing preferences --
int whole = 20; // 20ms is the TOTAL time we allow to update ALL 8 layers.
int part1 = whole/8; // each layer would be on for this long.
int part7 = whole-part1; // and be off this long while we update the other 7 layers.

//-- Layer counter --
uint8_t z = 0;

//-- AT328 timer --
//Timer0 is used by delay(), millis(), and micros().  We want to use that in normal loop()
//Timer1 is 16 bit. We don't need that resolution.
//Timer2 is 8 bit. Let's use that.

void InitTimer()
{
  //-- TCCR2 (Timer/Counter Control Register 2) --
  int8_t CS_prescaler = B100;
  // 000 No click source (Timer/counter stopped)
  // 001 No pre-scaling
  // 010 divide by 8 prescaler
  // 011 divide by 64 prescaler
  // 100 divide by 256 prescaler
  // 101 divide by 1024 prescaler
  // 110 external clock source on T1 pin (clock on falling edge)
  // 111 external clock source on T1 pin (clock on rising edge)

  int8_t COM_compareRegister = 0;
  int8_t WGM01_mode = 0;
  int8_t ICN_captureReg = 0;
  int8_t WGM23_mode = 0;

  noInterrupts();
  TCCR2A = COM_compareRegister + WGM01_mode;
  TCCR2B = ICN_captureReg + WGM23_mode + CS_prescaler;
  interrupts();  
}  

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led0, OUTPUT);     
  pinMode(led1, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  Study2();
  delay(part1);
}

void Study2()
{
  //-- Turn off previous layer --
  if (z==0) digitalWrite(led0, LOW);
  if (z==1) digitalWrite(led1, LOW);

  //-- Compute new layer --
  z++; if (z>=8) z=0;

  //-- Turn on new layer (will stay on till next time timer fires) --
  if (z==0) digitalWrite(led0, HIGH);
  if (z==1) digitalWrite(led1, HIGH);
}

