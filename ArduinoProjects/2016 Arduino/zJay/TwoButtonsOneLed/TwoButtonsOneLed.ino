// One button turns led on, the other turns led off
// Hari Wiguna 2016 for Jay

// Wire up first button to Arduino pin 2 and ground.
// Wire up second button to Arduino pin 3 and ground.
// Wire up LED to arduino pin 4 and ground.

int onButtonPin = 2;
int offButtonPin = 3;
int ledPin = 4;

int ledOn = LOW;
int ledOff = HIGH;
int ledState = ledOn;

void setup() {
  // put your setup code here, to run once:
  pinMode(onButtonPin, INPUT_PULLUP);
  pinMode(offButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(onButtonPin) == LOW) ledState = ledOn;
  if (digitalRead(offButtonPin) == LOW) ledState = ledOff;
  digitalWrite(ledPin, ledState);
  delay(100);
}
