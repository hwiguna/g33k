//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

#include <digitalWriteFast.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 13;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
bool isOn = true;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinModeFast(latchPin, OUTPUT);
  pinModeFast(clockPin, OUTPUT);
  pinModeFast(dataPin, OUTPUT);
  
  for (int i=0; i<8; i++) {
    pinModeFast(2+i, OUTPUT);
  }

  long start = micros();
  digitalWriteFast(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, B11111111); // Push Most significant BYTE first   
  shiftOut(dataPin, clockPin, MSBFIRST, B01111111);
  shiftOut(dataPin, clockPin, MSBFIRST, B00111111);
  shiftOut(dataPin, clockPin, MSBFIRST, B00011111);   
  shiftOut(dataPin, clockPin, MSBFIRST, B00001111);   
  shiftOut(dataPin, clockPin, MSBFIRST, B00000111);
  shiftOut(dataPin, clockPin, MSBFIRST, B0);
  shiftOut(dataPin, clockPin, MSBFIRST, B00001111); // Push Least significant byte last
  //return the latch pin high to signal chip that it 
  //no longer needs to listen for information
  digitalWriteFast(latchPin, HIGH);
  long finish = micros();
  
  Serial.begin(9600);
  Serial.println(finish-start);
}

void loop() {
  loopNormal();
} 

void unrolledFast()
{
  long d = 10; 
  digitalWriteFast(2,LOW); digitalWriteFast(3,HIGH); delayMicroseconds(d); 
  digitalWriteFast(3,LOW); digitalWriteFast(4,HIGH); delayMicroseconds(d); 
  digitalWriteFast(4,LOW); digitalWriteFast(5,HIGH); delayMicroseconds(d); 
  digitalWriteFast(5,LOW); digitalWriteFast(6,HIGH); delayMicroseconds(d); 
  digitalWriteFast(6,LOW); digitalWriteFast(7,HIGH); delayMicroseconds(d); 
  digitalWriteFast(7,LOW); digitalWriteFast(8,HIGH); delayMicroseconds(d); 
  digitalWriteFast(8,LOW); digitalWriteFast(9,HIGH); delayMicroseconds(d); 
  digitalWriteFast(9,LOW); digitalWriteFast(2,HIGH); delayMicroseconds(d); 
}


void loopFast()
{
  for (int i=0; i<8; i++) {
    int prev = i==0 ? 7 : i-1;
    digitalWriteFast(2+prev,LOW); // Turn off prev layer
    digitalWriteFast(2+i,HIGH); // Turn on this layer
    delay(500);
  }
}

void loopNormal()
{
  for (int i=0; i<8; i++) {
    int prev = i==0 ? 7 : i-1;
    digitalWrite(2+prev,LOW); // Turn off prev layer
    digitalWrite(2+i,HIGH); // Turn on this layer
    //delay(500);
  }
}

void CountUp() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, j);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(100);
  }

}
