#include "myServo.h"
#include <Arduino.h>

void pulse(Servo *Servo) {
  // drive pin high for a defined period of time.
  // this is declared as a friend function in Servo.h and thus has access to the private parts of Servo
  if ( Servo->_servoattached ) {
    digitalWrite(Servo->_servopin, HIGH);     // set servopin high for a certain period.
    // the following will prevent Wifi tasks to run for 1-2 msec
//    delayMicroseconds(1000 + 1000 * Servo->_servopos / 180);
    delayMicroseconds( map(Servo->_servopos, 0, 180, 1000, 2000) );
    digitalWrite(Servo->_servopin, LOW);
  }
};

Servo::Servo()
{
  _servoattached = false;
  // call servopulse every 20 msec.
  _servotimer.attach(0.02, pulse, this);
}

void Servo::detach() {
  _servoattached = false; // leave timer attached
  _servotimer.detach();
  pinMode( _servopin, INPUT);
}

void Servo::write(int pos) {
  _servopos = pos;
}

int Servo::read() {
  return _servopos;
}

boolean Servo::attached() {
  return _servoattached;
}

void Servo::attach(int pin) {
  pinMode( pin, OUTPUT);
  if (_servopos < 0 || _servopos > 180) _servopos = 0;
  _servopin = pin;
  _servoattached = true;
}


