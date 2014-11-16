byte triggerPin = 6;
byte echoPin = 7;

//=== INITIALIZATIONS ===

void InitializeRobot() {
  Serial.begin (9600);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


//=== DISTANCE SENSOR ===
float GetDistance() {
  delay(10); // Make sure we don't ping too often.
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triggerPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  float distance = (duration/2) / 74.07;
  return distance;
}

void PrintDistance()
{
  float d = GetDistance();
  Serial.println(d);
}

//=== M A I N ===

// the setup routine runs once when you press reset:
void setup() {
  InitializeRobot();
}

// the loop routine runs over and over again forever:
void loop() {
  PrintDistance();
  delay(100);
}

