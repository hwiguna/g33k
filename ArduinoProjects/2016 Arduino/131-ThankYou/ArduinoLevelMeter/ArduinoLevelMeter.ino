// Wiring/Arduino code:
// Read data from the serial and turn ON or OFF a light depending on the value

char val; // Data received from the serial port
int ledPin = 13; // Set the pin to digital I/O 4

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
  pinMode(2, OUTPUT); // Set pin as OUTPUT
  pinMode(3, OUTPUT); // Set pin as OUTPUT
  pinMode(4, OUTPUT); // Set pin as OUTPUT
  pinMode(5, OUTPUT); // Set pin as OUTPUT

  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  while (Serial.available()) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
  }
  switch (val)
  {
    case '0': Draw(0); break;
    case '1': Draw(1); break;
    case '2': Draw(2); break;
    case '3': Draw(3); break;
    case '4': Draw(4); break;
  }
  delay(100); // Wait 100 milliseconds for next reading
}

void Draw(int level)
{
  for (int i = 1; i <= level; i++)
    digitalWrite(2 + i - 1, LOW); // turn the LED on
  for (int i = level+1; i <= 4 ; i++)
    digitalWrite(2 + i - 1, HIGH); // turn the LED off
}

