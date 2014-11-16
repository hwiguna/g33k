volatile int count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);   // digital sensor is on digital pin 2
  digitalWrite(2,HIGH); // pullup resistor
  attachInterrupt(0, CountProc, CHANGE);
}

void loop()
{
  delay(10000);
}

void CountProc()
{
  Serial.println(++count);
}
