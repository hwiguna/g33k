// HariBot
// Hari Wiguna, 2014
// v0.1 - Testing the H-Bridge
// v0.2 - Distance Sensor, cleanup motor code
  // Is hand visible?
    // Yes, I see hand :-)
      // Move forward/backward to get to desired distance
    // No, I don't see hand :-(
      // Start waffling back and forth, increasing scan range if hand not found, decreasing range if hand found
      // When waffle angle is sufficiently small  

// Motor H-Bridge pins
byte motorPins[][2] = {
  {2,3}, // Left wheel
  {4,5},  // Right wheel
};

byte triggerPin = 6;
byte echoPin = 7;

int leftScanTime = 0;
int rightScanTime = 0;
int scanSpeed = 1;

int moveDuration = 100;
int rotateDuration = 1000;


//=== INITIALIZATIONS ===

void InitializeRobot() {
  Serial.begin (9600);

  pinMode(motorPins[0][0], OUTPUT);
  pinMode(motorPins[0][1], OUTPUT);
  pinMode(motorPins[1][0], OUTPUT);
  pinMode(motorPins[1][1], OUTPUT);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//=== MOTOR CONTROL ===

void Motor(byte whichMotor, int cmd)
{
  byte bridgeValues[2] = {0,0}; // Default both bridge pins to LOW
  switch (cmd) {
    case 1: bridgeValues[0]=1; break;  // cmd 1 means one direction
    case -1: bridgeValues[1]=1; break; // cmd -1 means the other direction, 0 means motor pins get two grounds.
  }
  digitalWrite(motorPins[whichMotor][0], bridgeValues[0]);
  digitalWrite(motorPins[whichMotor][1], bridgeValues[1]);
}

void Motors(int leftCmd, int rightCmd, int duration)
{
  Motor(0, leftCmd);
  Motor(1, rightCmd);
  delay(duration);
}

void Right() {
  Motors(+1,-1, rotateDuration);
}

void Left() {
  Motors(-1,+1, rotateDuration);
}

void Forward() {
  Motors(+1,+1, moveDuration);
}

void Backward() {
  Motors(-1,-1, moveDuration);
}

void Stop() {
  Motors(0,0, moveDuration);
}


//=== PRESET MOVES ===

void SquareDance() {
  Forward(); Right();   
  Forward(); Right(); 
  Forward(); Right();    
  Forward(); 
  Stop();   delay(1000);
}

void BackAndForth() {
  Forward();  Stop();
  Backward();  Stop();
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

void FindHand() {
  float distance = GetDistance();
  Serial.print(distance);
  Serial.print(" in. Diff=");
    
  // Is hand visible?
  if (distance > 2 && distance < 8) {
    // Yes, I see hand :-)
      // Move forward/backward to get to desired distance
      float diff = 5 - distance;
      float slop = 1;
      if (abs(diff) < slop) Stop();
      if (diff > slop) Backward();
      if (diff < -slop) Forward();
      Serial.print(diff);
      Serial.println("");
  } else {
    Stop();
    // No, I don't see hand :-(
      // Start waffling back and forth, increasing scan range if hand not found, decreasing range if hand found
      // When waffle angle is sufficiently small  
  }
}

void MotorTests() {
  Forward(); Stop();
  Backward(); Stop();
  Right(); Stop();
  Left(); Stop();
  Stop(); Stop();
}


//=== M A I N ===

// the setup routine runs once when you press reset:
void setup() {
  InitializeRobot();
}

// the loop routine runs over and over again forever:
void loop() {
  //MotorTests();
  FindHand();
}

