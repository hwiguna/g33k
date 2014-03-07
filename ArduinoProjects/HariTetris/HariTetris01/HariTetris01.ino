int longDelay = 5;
int work = longDelay;
int oldCol = 15;
int newCol = 0;

int minValue = 335;
int maxValue = 395;

void setup() {
  for (byte i=0; i<16; i++)
    pinMode(2+i,OUTPUT);
  
  cli(); // Stop interrupts

  TCCR0A = 0; // 
  TCCR0B = 0;
  TCNT0 = 0; // Counter
  
  // compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
  OCR0A = 255; //(16*10^6) / (2000*64) - 1; // OCR0A/OCR02A can be up to 255, OCR1A up to 65535
  
  TCCR0A |= (1 << WGM01); // Turn on CTC mode
  TCCR0B |= (1 << CS01) | (1 << CS00); // turn on bits for 64 prescaler
  
  TIMSK0 |= (1 << OCIE0A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}

ISR(TIMER0_COMPA_vect)
{
  work--;
  if (work==0) {
    work = longDelay;

    int sensorValue = analogRead(A5);
    int ledIndex = map(sensorValue, minValue, maxValue, 0,15);
    
    digitalWrite(2+oldCol,LOW);
    int newCol=ledIndex;
    digitalWrite(2+newCol,HIGH);
    oldCol=newCol;
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  //toggle0 = !toggle0;
  //digitalWrite(13,toggle0);
  //delay(1000);
}
