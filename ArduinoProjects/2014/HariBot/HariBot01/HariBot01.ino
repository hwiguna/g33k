byte leftA = 2;
byte leftB = 3;
byte rightA = 4;
byte rightB = 5;
byte modePin = 7;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(leftA, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(rightA, OUTPUT);
  pinMode(rightB, OUTPUT);

  pinMode(modePin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if (digitalRead(modePin))
    SquareDance();
  else
    BackAndForth();
}


void SquareDance() {
  Forward(); Right();   
  Forward(); Right(); 
  Forward(); Right();    
  Forward(); 
  Stop();   delay(1000);
}

void BackAndForth() {
  Forward();  Stop(); delay(1000); 
  Backward();  Stop(); delay(1000); 
}

void Right() {
  digitalWrite(leftA, HIGH);
  digitalWrite(leftB, LOW);

  digitalWrite(rightA, LOW);
  digitalWrite(rightB, HIGH);
  delay(500);
}

void Forward() {
  digitalWrite(leftA, HIGH);
  digitalWrite(leftB, LOW);

  digitalWrite(rightA, HIGH);
  digitalWrite(rightB, LOW);
  delay(1500);
}

void Backward() {
  digitalWrite(leftA, LOW);
  digitalWrite(leftB, HIGH);

  digitalWrite(rightA, LOW);
  digitalWrite(rightB, HIGH);
  delay(1500);
}

void Stop() {
  digitalWrite(leftA, LOW);
  digitalWrite(leftB, LOW);

  digitalWrite(rightA, LOW);
  digitalWrite(rightB, LOW);
}
