int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  int onDelay = max(50,sensorValue);
  int offDelay = sensorValue;

  digitalWrite(ledPin, HIGH);
  delay(onDelay);
  digitalWrite(ledPin, LOW);
  delay(offDelay);
}
