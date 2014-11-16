#include "MyClass.h"

void setup() {
  Serial.begin(9600);

  MyClass *myClass = new MyClass;
  int total = myClass->AddTwoInts(2,3);
  Serial.print ("AddTwoInts = ");
  Serial.println (total);
}

void loop() {
  // put your main code here, to run repeatedly:
}

