// Scanning 8 digital pins
// ANODE Rows

int anodePins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int pinIndex = 0;
const int ON = HIGH;
const int OFF = LOW;

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(anodePins[i], OUTPUT);
    digitalWrite(anodePins[pinIndex], OFF);
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(anodePins[pinIndex], ON);
  delay(1000);
  digitalWrite(anodePins[pinIndex], OFF);
  pinIndex++;
  if (pinIndex>7) pinIndex = 0;
}
