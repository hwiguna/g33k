/*
  Servotester

  A servo is connected to pin 14 and is sweeping much like the arduino example.
  This has an arduino-type library for controlling servos. Ticker is used to drive the servo pins
*/

#define servopin 14
#include <Ticker.h>
#include "myServo.h"

Servo servo;

void setup() {
  servo.attach(servopin);
}

int pos;
void loop() {
  for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    servo.write(pos);            // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    servo.write(pos);            // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

}
