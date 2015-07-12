#ifndef myServo_h
#define myServo_h

#include <Ticker.h>
#include <Arduino.h>

class Servo
{
public:
   Servo();
   void detach();
   void attach(int pin);
   void write(int pos);
   boolean attached();
   int read();
   int readpin();
   friend void pulse(Servo *Servo);
   
   private:
   int _servopin;
   int _servopos;
   boolean _servoattached;
   Ticker _servotimer;
};
#endif
