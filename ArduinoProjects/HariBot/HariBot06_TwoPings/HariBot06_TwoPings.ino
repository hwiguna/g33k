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
// v0.3 - Use PWM to compensate for weak 
// v0.5 - Using the extremely efficient Pololu DRV8835. Different pinouts!!!
// v0.6 - use two ping sensors to follow hand

// Motor H-Bridge (Pololu DRV8835) pins 
byte motorPins[][2] = {
  {2,3}, // Left wheel: 2=enable, 3=direction
  {4,5}, // Right wheel: 4=enable, 5=direction
};

byte pingPins[][2] = {
  {6,7},  // Trigger, Echo (HC-SR04 ultrasonic sensor)
  {8,9}
};

int moveDuration = 200;
int rotateDuration = 150;


//=== INITIALIZATIONS ===

void InitializeRobot() {
  Serial.begin (9600);

  for (byte i=0; i<2; i++) {
    for (byte j=0; j<2; j++) {
      pinMode(motorPins[i][j], OUTPUT);
    }
    pinMode(pingPins[i][0], OUTPUT); // Ultrasonic Trigger
    pinMode(pingPins[i][1], INPUT);  // Ultrasonic Echo
  }
}

//=== MOTOR CONTROL ===

void Motor(byte whichMotor, int isOn, int dir)
{
  digitalWrite( motorPins[whichMotor][0], isOn );
  digitalWrite( motorPins[whichMotor][1], dir );
}

void Right() {
  Motor(0, 1,0);
  Motor(1, 1,1);
  delay(rotateDuration);
  Stop();
}

void Left() {
  Motor(0, 1,1);
  Motor(1, 1,0);
  delay(rotateDuration);
  Stop();
}

void Forward() {
  Motor(0, 1,1);
  Motor(1, 1,1);
  delay(moveDuration);
  Stop();
}

void Backward() {
  Motor(0, 1,0);
  Motor(1, 1,0);
  delay(moveDuration);
  Stop();
}

void Stop() {
  Motor(0, 0,0);
  Motor(1, 0,0);
}

//=== DISTANCE SENSOR ===

float GetDistance(byte triggerPin, byte echoPin) {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triggerPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = min( (duration/2) / 74.07, 20.0 );
  return distance;
}

void FollowHand() {
  bool debug = false;

  float distance = GetDistance(pingPins[0][0], pingPins[0][1]);
  delay(10);
  float distance2 = GetDistance(pingPins[1][0], pingPins[1][1]);
  delay(10);
  
  float diff = distance - distance2;
  
  if (debug) 
  {
    Serial.print(distance);
    Serial.print(" in  ");
    Serial.print(distance2);
    Serial.print(" in ");
    Serial.print(diff);
    Serial.print(" in ");
  }
  
  //-- Turn left or right --
  if ( distance < 5 || distance2 < 5) {
    if (diff <-1) {
      if (debug) Serial.print(  " <-- ");
      Left();
    }
    
    if (diff >+1) {
      if (debug) Serial.print(  " --> ");
      Right();
    }  
  }
  
  //-- Go Forward --
  if ( distance > 5 && distance < 8 && distance2 > 5 && distance2 < 8) {
    if (debug) Serial.print(  " FWD");
    Forward();
  }
  
  
  //-- Go Backward --
  if ( distance < 3 && distance2 < 3) {
    if (debug) Serial.print(" REV");
    Backward();
  }
  
  if (debug) Serial.println();
}

void MotorTests() {
  Serial.println("Forward"); Forward(); 
  Serial.println("Stop"); Stop();
  Serial.println("Backward"); Backward();
  Serial.println("Stop"); Stop();
  Serial.println("Right"); Right();
  Serial.println("Stop"); Stop();
  Serial.println("Left"); Left();
  Serial.println("Stop"); Stop();
}


//=== M A I N ===

// the setup routine runs once when you press reset:
void setup() {
  InitializeRobot();
}

// the loop routine runs over and over again forever:
void loop() {
  //MotorTests();
  //Left();
  //Right();
  //Forward();
  FollowHand();
}

