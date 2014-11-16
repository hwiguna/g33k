#include "Arduino.h"
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

