// Scanning 8 digital pins
// GREEN columns

//int greenPins[8] = {0, 1, 2, 3, 7, 8, 9, 10};
int greenPins[8] = {10,9,8,7,3,2,1,0};
int pinIndex = 0;
const int ON = LOW;
const int OFF = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(greenPins[i], OUTPUT);
    digitalWrite(greenPins[pinIndex], OFF);
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(greenPins[pinIndex], ON);
  delay(1000/16);
  digitalWrite(greenPins[pinIndex], OFF);
pinIndex++;
  if (pinIndex>7) pinIndex = 0;


    digitalWrite(slaveSelectPin, LOW); // LOW = Hey, SPI slave, PAY ATTENTION to me, your master!
  SPI.transfer('H'); // Send something else
  SPI.transfer('\n'); // Send something else
  //SPI.transfer(count); // Send something
  digitalWrite(slaveSelectPin, HIGH); // HIGH= You can ignore me now, I'm going to talk to other slaves!

}
