// Parking Helper
// by Hari Wiguna, 2015
// Heavily based on Arduino Ping example

const int ON = LOW;
const int OFF = HIGH;

// Distance sensor is HC-SR04
const int pingPin = 12; // TRIG
const int echoPin = 13; // ECHO

int prevBar = 0;

void setup() {
  //-- Initialize led bargraph pins --
  for (int i = 0; i < 10; i++)
  {
    pinMode(2 + i, OUTPUT);
    digitalWrite(2 + i, OFF);
  }
  
  //-- Initialize distance sensor pins --
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  // Send out a 5 microsecond pulse
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Listen for that pulse to come back
  long duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  long cm = microsecondsToCentimeters(duration);

  // Convert cm to bar graph
  int bar = map(cm, 10, 70, 9, 0);

  // only update bar graph if value changed
  if (bar != prevBar) {
    digitalWrite(2 + prevBar, OFF);
    digitalWrite(2 + bar, ON);
    prevBar = bar;
  }

  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
