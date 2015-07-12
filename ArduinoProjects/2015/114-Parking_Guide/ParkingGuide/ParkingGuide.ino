const int ON = LOW;
const int OFF = HIGH;

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<8;i++)
  {
    pinMode(2+i,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i=0; i<8;i++)
  {
    digitalWrite(2+i,ON);
    delay(100);
    digitalWrite(2+i,OFF);
  }
}
