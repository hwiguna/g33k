#include "Arduino.h"  // Allows us to use Arduino types and functions within this class
#include "MyClass.h"

MyClass::MyClass() // Constructor
{
}

MyClass::~MyClass() // Destructor
{
}

int MyClass::AddTwoInts(int int1, int int2)
{
  return int1 + int2;
}

