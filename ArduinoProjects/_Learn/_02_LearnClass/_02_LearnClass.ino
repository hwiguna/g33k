#include "MyClass.h"

void setup() {
  Serial.begin(9600);

  MyClass *myClass = new MyClass;
  int total = myClass->AddTwoInts(2,3);
  Serial.print ("AddTwoInts = ");
  Serial.println (total);
  
  int* intArr = myClass->GetIntArray();
  Serial.print ("intArr[1] = ");
  Serial.println (intArr[1]);
  
  int** intMatrix = myClass->GetIntMatrix();
  Serial.print ("intMatrix[1][2] = ");
  Serial.println (intMatrix[1][2]);
  
  int** intShared = myClass->GetFromShared();
  Serial.print ("intShared[1][2] = ");
  Serial.println (intShared[1][2]);
}

void loop() {
  // put your main code here, to run repeatedly:
}

