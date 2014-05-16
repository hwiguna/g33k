// v02 - count pulses within x seconds

volatile int count = 0;
unsigned long sampleSeconds = 5; // How many seconds are we sampling?

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);   // digital sensor is on digital pin 2
  digitalWrite(2,HIGH); // pullup resistor
}

void loop()
{
  count=0;
  attachInterrupt(0, CountProc, RISING); // CHANGE

  delay( sampleSeconds * 1000 );
  detachInterrupt(0);

  unsigned long pulseCountPerRotation = 20;
  float rotationCount = count / pulseCountPerRotation;
  Serial.print(count);
  Serial.print(" pulses. ");
  Serial.print(rotationCount);
  Serial.print(" revolutions in ");
  Serial.print(sampleSeconds);
  Serial.print(" seconds. ");
  Serial.print(rotationCount/sampleSeconds);
  Serial.println(" revolutions/second.");
}

void CountProc()
{
  count++;
  //Serial.println(count);
}
