
// Handy way to pass around X and Y as one variable

#ifndef Point_h
#define Point_h

#include "U8glib.h"

class Point
{
  public:
    void Set(int x, int y);
    int X;
    int Y;
};

#endif
