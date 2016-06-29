
// Handy way to pass around X and Y as one variable

#include "U8glib.h"
#include "Point.h"

void Point::Set(int x, int y)
{
  X = x;
  Y = y;
}
