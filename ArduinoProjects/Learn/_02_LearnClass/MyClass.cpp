#include "Arduino.h"  // Allows us to use Arduino types and functions within this class
#include "MyClass.h"

int shared[3][4] = {
  {1,2,3,4},  
  {11,12,13,14},  
  {21,22,23,24},  
};

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

int* MyClass::GetIntArray()
{
  //int arr[] = {0,1,2}; // Can't do this in a class method :-(
  int *arr = (int *)malloc( sizeof(int)*3 );
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;
  return arr;
}

int** MyClass::GetIntMatrix()
{
  int **arr = (int **)malloc( sizeof(int)*3*4 );
  arr[0][0] = 0;  arr[0][1] = 1;  arr[0][2] = 2;  arr[0][3] = 3;
  arr[1][0] = 10;  arr[1][1] = 11;  arr[1][2] = 12;  arr[1][3] = 13;
  arr[2][0] = 20;  arr[2][1] = 21;  arr[2][2] = 22;  arr[2][3] = 23;
  return arr;
}

int** MyClass::GetFromShared()
{
  // This does not  return correct array elements
  return (int **)shared; 

// Neither does this  
//  int **dup = (int **) malloc( sizeof(shared) );
//  memcpy(shared,dup, sizeof(shared));
//  return dup;

// Nor this
//  int dup[3][4];
//  for (byte i=0; i<3; i++) {
//    for (byte j=0; j<4; j++) {
//      dup[i][j] = shared[i][j];
//    }  
//  }
//  return (int **)dup;
}

