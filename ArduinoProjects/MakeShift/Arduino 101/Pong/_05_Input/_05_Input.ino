int ledPin = 4;
int buttonPin = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ledPin, OUTPUT);   // initialize digital pin 13 as an output.
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    delay(500);
  }
}
