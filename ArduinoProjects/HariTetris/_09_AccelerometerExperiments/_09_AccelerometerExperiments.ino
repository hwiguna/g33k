
// Towards Arduino Tetris

// This code only does not have the shift register code.
// Open Serial Monitor in Arduino IDE at 9600baud to see the data sent back.
// For some reason analogRead(A3) always returns 0 when interrupt is enabled?!

const int xSensor = A5;
const int ySensor = A4;
//const int zSensor = A3; For some reason analogRead(A3) always returns 0 when interrupt is enabled?!

int longDelay = 50;
int work = longDelay;

//int minValue = 335;
//int maxValue = 395;

ISR(TIMER0_COMPA_vect)
{
  work--;
  if (work==0) {
    work = longDelay;

  }
}

void setup() {
  Serial.begin(9600);
//  pinMode(zSensor,INPUT);
//  analogReference(DEFAULT);
  
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


void loop() {
//    int zValue = analogRead(zSensor);
    int xValue = analogRead(xSensor);
    int yValue = analogRead(ySensor);
    
    Serial.print(xValue); Serial.print(", "); 
    Serial.print(yValue); Serial.println(); 
//    Serial.print(zValue); Serial.println(); 
    delay(500);
}

