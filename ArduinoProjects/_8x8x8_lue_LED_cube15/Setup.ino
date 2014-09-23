void SetupPins()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i=0; i<8; i++) {
    pinMode(2+i, OUTPUT);
  }
}

void SetupCapSense()
{
  pinMode(14+0,OUTPUT);
  pinMode(14+1,OUTPUT); //15
  pinMode(14+2,OUTPUT); //16
  pinMode(14+3,OUTPUT); //17
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  //cs_14_15.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}


void SetupTimer()
{
  cli();
  // Reset any PWM that arduino may have setup automatically
  TCCR2A = 0;
  TCCR2B = 0;

  TCCR2A |= (1 << WGM21); // CTC mode. Reset counter when OCR2 is reached

  TCCR2B |= (1 << CS21) | (1 << CS22); // Prescaler = 256
  //TCCR2B |= (1 << CS20) | (1 << CS22); // Prescaler = 128
  OCR2A = 70; // Fire interrupt when timer2 has looped 80 times

  TCNT2 = 0; // initial counter value = 0;
  TIMSK2 |= (1<<OCIE2A); // Enable CTC interrupt
  sei();
}

ISR (TIMER2_COMPA_vect)
{
  Refresh();
}

void Refresh(void) // WITHOUT the added delayMicroseconds, this routine takes 8052 microseconds
{
  noInterrupts();

  //-- Compute new layer --
  int8_t prevLayer = gZ;
  gZ++; 
  if (gZ>=8) gZ=0;

  // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
  digitalWrite(latchPin, LOW);

  //-- Spit out the bits --
  DrawLayer(gZ);

  //-- Turn off previous layer --
  digitalWrite(2+prevLayer,LOW); // Turn off prev layer

  //-- Turn on this layer --
  digitalWrite(2+gZ,HIGH); // Turn on this layer


  // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
  digitalWrite(latchPin, HIGH);

  interrupts();
}

void PreComputes()
{
  for (int8_t index=0; index < sineMaxIndex; index++)
  {
    float a = pi*2 * index / sineMaxIndex;
    sineArray[ index ] = 4 + (sin(a) * 3.5);
  }
  
}


