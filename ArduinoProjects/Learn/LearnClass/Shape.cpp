#include "Arduino.h"
#include "Shape.h"

//bool ShapeArrays[][4] = {
//  {0,0,0,0},
//  {0,0,0,0},
//  {0,0,0,0},
//  {0,0,0,0} };
int arr[] = {10,20,30};

Shape::Shape() {
}

int Shape::Hello() {
    return 1; //ShapeArrays[0];
}

int Shape::Seven() {
  return 7;
}

int* Shape::GetArr()
{
  int *a = (int *)malloc(6);
  a[0]=0;
  a[1]=1;
  a[2]=2;
  return a;
}

int* Shape::GetArr2()
{
  return arr;
}
