void Bresenham3D(int8_t x1, int8_t y1, int8_t z1, const int8_t x2, const int8_t y2, const int8_t z2, const byte mode)
{
  // This routine is from:
  //https://gist.github.com/yamamushi/5823518
  // I only adapted it for my sketch.
  
  int8_t i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
  int8_t point[3];
  
  point[0] = x1;
  point[1] = y1;
  point[2] = z1;
  dx = x2 - x1;
  dy = y2 - y1;
  dz = z2 - z1;
  x_inc = (dx < 0) ? -1 : 1;
  l = abs(dx);
  y_inc = (dy < 0) ? -1 : 1;
  m = abs(dy);
  z_inc = (dz < 0) ? -1 : 1;
  n = abs(dz);
  dx2 = l << 1;
  dy2 = m << 1;
  dz2 = n << 1;
  
  if ((l >= m) && (l >= n)) {
      err_1 = dy2 - l;
      err_2 = dz2 - l;
      for (i = 0; i < l; i++) {
          //output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
          if (mode) SetDot(point[0], point[1], point[2]); else ClearDot(point[0], point[1], point[2]);
          if (err_1 > 0) {
              point[1] += y_inc;
              err_1 -= dx2;
          }
          if (err_2 > 0) {
              point[2] += z_inc;
              err_2 -= dx2;
          }
          err_1 += dy2;
          err_2 += dz2;
          point[0] += x_inc;
      }
  } else if ((m >= l) && (m >= n)) {
      err_1 = dx2 - m;
      err_2 = dz2 - m;
      for (i = 0; i < m; i++) {
          //output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
          if (mode) SetDot(point[0], point[1], point[2]); else ClearDot(point[0], point[1], point[2]);
          if (err_1 > 0) {
              point[0] += x_inc;
              err_1 -= dy2;
          }
          if (err_2 > 0) {
              point[2] += z_inc;
              err_2 -= dy2;
          }
          err_1 += dx2;
          err_2 += dz2;
          point[1] += y_inc;
      }
  } else {
      err_1 = dy2 - n;
      err_2 = dx2 - n;
      for (i = 0; i < n; i++) {
          //output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
          if (mode) SetDot(point[0], point[1], point[2]); else ClearDot(point[0], point[1], point[2]);
          if (err_1 > 0) {
              point[1] += y_inc;
              err_1 -= dz2;
          }
          if (err_2 > 0) {
              point[0] += x_inc;
              err_2 -= dz2;
          }
          err_1 += dy2;
          err_2 += dx2;
          point[2] += z_inc;
      }
  }
  //output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
  if (mode) SetDot(point[0], point[1], point[2]); else ClearDot(point[0], point[1], point[2]);
}

void DrawLine3(int8_t x0,int8_t y0, int8_t x1,int8_t y1, int8_t z)
{
    boolean steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) { Swap(&x0, &y0); Swap(&x1, &y1); }
    if (x0 > x1) { Swap(&x0, &x1); Swap(&y0,&y1); }
    int dX = (x1 - x0);
    int dY = abs(y1 - y0);
    int err = (dX / 2);
    int ystep = (y0 < y1 ? 1 : -1);
    int y = y0;
 
    for (int x = x0; x <= x1; ++x)
    {
        if (steep) SetDot(y, x, z); else SetDot(x, y, z);
        err = err - dY;
        if (err < 0) { y += ystep;  err += dX; }
    }
}

void EraseLine3(int8_t x0,int8_t y0, int8_t x1,int8_t y1, int8_t z)
{
    boolean steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) { Swap(&x0, &y0); Swap(&x1, &y1); }
    if (x0 > x1) { Swap(&x0, &x1); Swap(&y0,&y1); }
    int dX = (x1 - x0);
    int dY = abs(y1 - y0);
    int err = (dX / 2);
    int ystep = (y0 < y1 ? 1 : -1);
    int y = y0;
 
    for (int x = x0; x <= x1; ++x)
    {
        if (steep) ClearDot(y, x, z); else ClearDot(x, y, z);
        err = err - dY;
        if (err < 0) { y += ystep;  err += dX; }
    }
}


void CalcLine3D(int8_t x1, int8_t y1, int8_t z1, const int8_t x2, const int8_t y2, const int8_t z2, byte mode)
{
  Bresenham3D(x1,y1,z1, x2,y2,z2, mode);
}

void DrawLine3D(int8_t x0, int8_t y0, int8_t z0, const int8_t x1, const int8_t y1, const int8_t z1)
{
  CalcLine3D(x0,y0,z0, x1,y1,z1, 1);
}

void EraseLine3D(int8_t x0, int8_t y0, int8_t z0, const int8_t x1, const int8_t y1, const int8_t z1)
{
  CalcLine3D(x0,y0,z0, x1,y1,z1, 0);
}

void DrawLine2(int8_t x0,int8_t y0, int8_t x1,int8_t y1, int8_t z)
{
   int dx = abs(x1-x0);
   int dy = abs(y1-y0);
   int sx = (x0 < x1) ? 1 : -1;
   int sy = (y0 < y1) ? 1 : -1;
   int err = dx-dy;

  Serial.print("dx, dy, sx, sy, err =");
  Serial.print(dx);  Serial.print(", ");
  Serial.print(dy);  Serial.print(", ");
  Serial.print(sx);  Serial.print(", ");
  Serial.print(sy);  Serial.print(", ");
  Serial.println(err);
 
   while (true)
   {
//     Serial.print("x0,y0 = ");
//     Serial.print(x0);  Serial.print(", ");
//     Serial.println(y0);
     SetDot(x0,y0, z);
     if ((x0 == x1) && (y0 == y1)) exit;
     int e2 = 2*err;
     if (e2 > -dy)
    { 
       err = err - dy;
       x0 = x0 + sx;
    }
     if (e2 < dx) 
     {
       err = err + dx;
       y0 = y0 + sy;
     }
   }
}

void SetDot(int8_t x,int8_t y, int8_t z)
{
  //noInterrupts();
  bitSet(cube[y][z], x);

//  Serial.print("X,Y,Z = ");
//  Serial.print(x);  Serial.print(",");
//  Serial.print(y);  Serial.print(",");
//  Serial.println(z);

  //interrupts();
}

void ClearDot(int8_t x,int8_t y,int8_t z)
{
  bitClear(cube[y][z], x);
}

void SetLayer(int8_t z, int8_t xByte)
{
  //z = Wrap(z);
  for (int8_t y=0; y<8; y++) {
    cube[y][z] = xByte;
    //for (int8_t x=0; x<8; x++) {
    //  if (xByte==0) ClearDot(x,y,z); else SetDot(x,y,z);
    //}
  }
}
void CalcLine(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, byte mode)
{
  byte parallelAxis = 0; // 0=x, 1=y, 2=z
  int8_t a1, a2, b1, b2;
  if (x1!=x2) {
    parallelAxis = 0; 
    a1=x1; 
    a2=x2; 
  } // parallel to X
  if (y1!=y2) {
    parallelAxis = 1; 
    a1=y1; 
    a2=y2; 
  } // parallel to Y
  if (z1!=z2) {
    parallelAxis = 2; 
    a1=z1; 
    a2=z2; 
  } // parallel to Z
  for (int8_t p=a1; p<=a2; p++) {
    int8_t x,y,z;
    switch (parallelAxis) {
    case 0: 
      x=p; 
      y=y1; 
      z=z1; 
      break; // parallel to X
    case 1: 
      x=x1; 
      y=p; 
      z=z1; 
      break; // parallel to Y
    case 2: 
      x=x1; 
      y=y1; 
      z=p; 
      break; // parallel to Z
    }
    if (mode==1) SetDot(x,y,z); 
    else ClearDot(x,y,z);
  }
}

void DrawLine(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2)
{
  CalcLine(x1,y1,z1, x2,y2,z2, 1);
}

void EraseLine(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2)
{
  CalcLine(x1,y1,z1, x2,y2,z2, 0);
}

void CalcRect(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2, byte mode)
{
  byte tangentAxis = 0; // 0=x, 1=y, 2=z
  int8_t a1, a2, b1, b2;
  if (y1!=y2 && z1!=z2) {
    tangentAxis = 0; 
    a1=y1; 
    a2=y2; 
    b1=z1; 
    b2=z2;
  } // YZ Plane
  if (x1!=x2 && z1!=z2) {
    tangentAxis = 1; 
    a1=x1; 
    a2=x2; 
    b1=z1; 
    b2=z2;
  } // XZ plane
  if (x1!=x2 && y1!=y2) {
    tangentAxis = 2; 
    a1=x1; 
    a2=x2; 
    b1=y1; 
    b2=y2;
  } // XY Plane

//      Serial.print("a1,a2 b1,b2 t = ");
//      Serial.print(a1);  Serial.print(",");
//      Serial.print(a2);  Serial.print(" ");
//      Serial.print(b1);  Serial.print(",");
//      Serial.print(b2);  Serial.print(" ");
//      Serial.println(tangentAxis);

  for (int8_t p=a1; p<=a2; p++) {
    for (int8_t q=b1; q<=b2; q++) {
      int8_t x,y,z;
      switch (tangentAxis) {
      case 0: 
        x=x1; 
        y=p; 
        z=q; 
        break; // YZ Plane
      case 1: 
        x=p; 
        y=y1; 
        z=q; 
        break; // XZ plane
      case 2: 
        x=p; 
        y=q; 
        z=z1; 
        break; // XY Plane
      }

//      Serial.print("x,y,z = ");
//      Serial.print(x);  Serial.print(",");
//      Serial.print(y);  Serial.print(",");
//      Serial.print(z);  Serial.print("  mode=");
//      Serial.println(mode);

      if (mode==1) SetDot(x,y,z); 
      else ClearDot(x,y,z);
    }
  }
}

void DrawRect(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2)
{
  CalcRect(x1,y1,z1, x2,y2,z2, 1);
}

void EraseRect(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2)
{
  CalcRect(x1,y1,z1, x2,y2,z2, 0);
}


