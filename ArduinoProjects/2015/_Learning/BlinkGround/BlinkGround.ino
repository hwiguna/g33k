void setup() {
  pinMode(2,INPUT); // Set to input so we can float it
  digitalWrite(2,LOW); // no pullup resistor = float this pin
}

void loop() {
  // Ground
  pinMode(2,OUTPUT); // switching pin 2 to output will show its state (LOW)
  delay(1000);
  // Float
  pinMode(2,INPUT); // switching pin 2 to input will return pin to float
  delay(5z000);
}
