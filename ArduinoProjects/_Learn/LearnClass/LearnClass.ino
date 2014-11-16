#include "MyClass.h"

void setup() {
  Serial.begin(9600);

  MyClass *myClass = new MyClass;
  int total = myClass->AddTwoInts(2,3);
  Serial.print ("AddTwoInts = ");
  Serial.println (total);

  Serial.println();
//
//  Shape* myShape = new Shape;
//  Shape* myShape2 = new Shape;
//  Serial.print ("Loop");
//  int x = myShape->Seven();
//  Serial.println(x);
//
//  int *y = myShape->GetArr2();
//  int *eve = (int*)malloc(6);
//  memcpy(y,eve, sizeof(y));
//  eve[2]=2;
//  Serial.println(eve[2]);
//  Serial.println(y[2]);
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

