int inPin = 4;
int outPin = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(inPin,INPUT);
pinMode(outPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(inPin);
  digitalWrite(outPin, state);
  delay(100);
}
