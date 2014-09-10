void MainShow()
{
  SnakeSpiralDown();

  FillLayerLeftToRight(0);
  FillWallDownUp(7);
  FillLayerRightLeft(7);
  DropOneCenterLine(0);
  FillWallFromCenter(0);
  FillFrontAndBackRightLeft();
  delay(250);
  CubeShrink();
  DropFromCenter();
  delay(250);
  SpreadFromCenter(0);
  RaiseCorners();
  ZipTop();
  delay(500);
  CollapseToFloor();

//  RaiseSeaLevel();
//  delay(500);
//  RippleFadeIn();
//  RippleToRight();

  FoldUp();
  delay(500);
  FoldFromLeft();
  delay(500);
  FoldTopToRight();
  delay(500);
  
  PinWheel(7);
  delay(500);
  PinWheel(0);

  CubeShrink();
  delay(64);
  CubeAllOff();

  EdgeBurst2(0);  FollowLine(0,7,0, 1,0,0);
  EdgeBurst2(1);  FollowLine(7,7,0, 0,-1,0);
  EdgeBurst2(2);  FollowLine(7,0,0, -1,0,0);
  EdgeBurst2(3);  //FollowLine(0,0,0, 0,1,0);

//  DotToRect();
//  FillBottom();
}

void Pyramid3()
{
  if (abs(pot0-oldPot0)>100)
  {
    oldPot0 = pot0;
    CubeAllOff();
    for (int8_t n=0; n<4; n++)
    {
      int8_t z = n * map(pot0, 200,1000, 1,7) / 3;
      DrawRect(n,n,z, 7-n,7-n,z); // XY plane
      if (z+1<8) DrawRect(n,n,z+1, 7-n,7-n,z+1); // XY plane
    }
  }
}

void Pyramid2()
{
  for (int8_t n=0; n<4; n++)
  {
    int8_t z = n*2;
    DrawRect(n,n,z, 7-n,7-n,z); // XY plane
    DrawRect(n,n,z+1, 7-n,7-n,z+1); // XY plane
  }
}

void Pyramid1()
{
  int8_t h = 4;
  
  // Base
  DrawLine3D(0,0,0, 6,0,0);
  DrawLine3D(6,6,0, 6,0,0);
  DrawLine3D(6,6,0, 0,6,0);
  DrawLine3D(0,0,0, 0,6,0);
  
  // Sides
  DrawLine3D(0,0,0, 3,3,h);
  DrawLine3D(6,0,0, 3,3,h);
  DrawLine3D(6,6,0, 3,3,h);
  DrawLine3D(0,6,0, 3,3,h);
}

void TestDrawLine3D()
{
  // Edges
//  DrawLine3D(0,0,0, 7,0,0);
//  DrawLine3D(0,0,0, 0,7,0);
//  DrawLine3D(0,0,0, 0,0,7);
//
//  // XY Plane
//  DrawLine3D(0,0,0, 7,4,0);
//  DrawLine3D(0,0,0, 7,7,0);
//  DrawLine3D(0,0,0, 4,7,0);
//
//  // XZ Plane
//  DrawLine3D(0,0,0, 7,0,4);
//  DrawLine3D(0,0,0, 7,0,7);
//  DrawLine3D(0,0,0, 4,0,7);
//
//  // YZ Plan
//  DrawLine3D(0,0,0, 0,7,4);
//  DrawLine3D(0,0,0, 0,7,7);
//  DrawLine3D(0,0,0, 0,4,7);
}
void RunTests()
{
  Serial.begin(9600);

  Serial.print("TestCubeAllOff = ");
  Serial.println(TestCubeAllOff());

  Serial.print("TestRefresh = ");
  Serial.println(TestRefresh());    // 8052 micro seconds

  Serial.end();
}

long TestCubeAllOff()
{
  long start = micros();
  CubeAllOff();
  long finish = micros();
  return finish-start;
}

long TestRefresh()
{
  long start = micros();
  Refresh();
  long finish = micros();
  return finish-start;
}

void TestPattern3()
{
  CubeAllOff();
  delay(500);
  CubeAllOn();
  delay(500);
}


void BottomUp()
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=0; x<8; x++) {
      for (int8_t y=0; y<8; y++) {
        SetDot(x,y,z); 
      }
    }
    delay(64);
    CubeAllOff();
  }
}


void OneWall()
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=0; x<8; x++) {
      for (int8_t y=7; y<8; y++) {
        SetDot(x,y,z); 
      }
    }
  }
}

void LeftRight()
{
  for (int8_t x=0; x<8; x++) {
    for (int8_t z=0; z<8; z++) {
      for (int8_t y=7; y<8; y++) {
        SetDot(x,y,z); 
      }
    }
    delay(64);
    CubeAllOff();
  }
}

void TurnOnLayer(int8_t z)
{
  int8_t prev = z==0 ? 7 : z-1;

  // Prepare for data. Shift data to shift registers but do not reflect it on the outputs yet.
  digitalWrite(latchPin, LOW);

  //-- Spit out the bits --
  DrawLayer(z);

  //-- Turn off previous layer --
  digitalWrite(2+prev,LOW); // Turn off prev layer
}

void TurnOffLayer(int8_t z)
{
  // All data ready. Instantly reflect all 64 bits on all 8 shift registers to the led layer.
  digitalWrite(latchPin, HIGH);

  //-- Turn on this layer --
  digitalWrite(2+z,HIGH); // Turn on this layer
}

void DrawLayer(int8_t z)
{
  // Spit out all 64 bits for the layer.
  for (int8_t y=0; y<8; y++) {
    shiftOut(dataPin, clockPin, MSBFIRST, ~cube[y][z]); // Push Most significant BYTE first   
  }  
}

void LayerOn(int8_t z)
{
  for (int8_t y=0; y<8; y++) {
    for (int8_t x=0; x<8; x++) {
      SetDot(x,y,z);
    }  
  }  
}

void CubeAllOn()
{
  //noInterrupts();
  for (int8_t z=0; z<8; z++) {
    for (int8_t y=0; y<8; y++) {
      for (int8_t x=0; x<8; x++) {
        SetDot(x,y,z);
      }  
    }  
  }  
  //interrupts();
}

void CubeAllOff()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z, 0x00);
  }  
}

void CubeUp()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z, 0xFF);
    delay(animSpeed);
    SetLayer(z, 0x00);
  }  
}

void CubeDown()
{
  for (int8_t z=7; z>=0; z--) {
    SetLayer(z, 0xFF);
    delay(animSpeed);
    SetLayer(z, 0x00);
  }  
}

void CubeLeftRight()
{
  for (int8_t x=0; x<8; x++) {
    SetXPlane(x);
    delay(animSpeed);
    CubeAllOff();
  }  
}

void CubeRightLeft()
{
  for (int8_t x=7; x>=0; x--) {
    SetXPlane(x);
    delay(animSpeed);
    CubeAllOff();
  }  
}

void SetXPlane(int8_t x)
{
  x = Wrap(x);
  int8_t xPattern = 1 << x;
  for (int8_t z=0; z<8; z++) {
    for (int8_t y=0; y<8; y++) {
      cube[y][z] = xPattern;
    }
  }
}

void TestPattern1()
{
  //int8_t y = 7;
  for (int8_t x=0; x<8; x++) {
    for (int8_t y=0; y<8; y++) {
      SetDot(x,y,0); 
      SetDot(7-x,y,1);
    }

    delay(20);

    for (int8_t y=0; y<8; y++) {
      ClearDot(x,y,0); 
      ClearDot(7-x,y,1);
    }
  }
}

void TestPattern2_Scan_one_layer(int8_t z)
{
  for (int8_t y=0; y<8; y++) {
    for (int8_t x=0; x<8; x++) {
      SetDot(x,y,z);
      delay(300);
      ClearDot(x,y,z);
    }
  }
}

void One_Pixel_Up_a_wall(int8_t y)
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=7; x>=0; x--) {
      SetDot(x,y,z);
      delay(64);
      ClearDot(x,y,z);
    }
  }
}

void Line_Up_a_wall(int8_t y)
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=7; x>=0; x--) {
      SetDot(x,y,z);
    }
    delay(64);
    CubeAllOff();
  }
}


void TestPattern_scan_all_layers()
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t y=0; y<8; y++) {
      for (int8_t x=0; x<8; x++) {
        SetDot(x,y,z);
        delay(64);
        ClearDot(x,y,z);
      }
    }
  }
}

void TestPattern4_Scan_one_wall()
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t x=7; x>=0; x--) {
      SetDot(x,7,z);
      delay(64);
      ClearDot(x,7,z);
    }
  }
}

void TestPattern5_swipe_wall_up()
{
  for (int8_t z=0; z<8; z++) {
    SetLayer(z,0xFF);
    //for (int8_t x=0; x<8; x++) SetDot(x,7,z);
    //for (int8_t y=3; y<8; y++) for (int8_t x=0; x<8; x++) SetDot(x,y,z);
    delay(64);
    //SetLayer(z,0x00);
    CubeAllOff();
    //for (int8_t x=0; x<8; x++) ClearDot(x,7,z);
    //for (int8_t y=3; y<8; y++) for (int8_t x=0; x<8; x++) ClearDot(x,y,z);
  }
}


void BottomCorner()
{
  for (int8_t x=0; x<1; x++) {
    for (int8_t y=7; y<8; y++) {
      SetDot(x,y,1); 
    }
  }
}

void FillLayerLeftToRight(int8_t z)
{
  for (int8_t x=1; x<8; x++) {
    for (int8_t y=0; y<8; y++) {
      SetDot(x,y,z);
    }
    delay(64);
  }
}

void FillWallDownUp(int8_t x)
{
  for (int8_t z=0; z<8; z++) {
    for (int8_t y=0; y<8; y++) {
      SetDot(x,y,z);
    }
    delay(64);
  }
}


void FillLayerRightLeft(int8_t z)
{
  for (int8_t x=7; x>=0; x--) {
    for (int8_t y=0; y<8; y++) {
      SetDot(x,y,z);
    }
    delay(64);
  }
}

void DropOneCenterLine(int8_t x)
{
  for (int8_t z=7; z>=0; z--) {
    SetDot(x,3,z);
    SetDot(x,4,z);
    delay(64);
  }
}

void FillWallFromCenter(int8_t x)
{
  for (int8_t y=1; y<4; y++) {
    for (int8_t z=0; z<8; z++) {
      SetDot(x,3-y,z);
      SetDot(x,4+y,z);
    }
    delay(64);
  }
}

void FillFrontAndBackRightLeft()
{
  for (int8_t x=0; x<8; x++) {
    for (int8_t z=0; z<8; z++) {
      SetDot(x,0,z);
      SetDot(x,7,z);
    }
    delay(64);
  }
}


void CubeShrink()
{
  int8_t cubeSize = 5;
  for (int8_t n=1; n<4; n++) {
    CubeAllOff();
    DrawRect(n,n,n, n, n+cubeSize, n+cubeSize); // YZ plane
    DrawRect(7-n,n,n, 7-n, n+cubeSize, n+cubeSize); // YZ plane
    DrawRect(n,n,n, n+cubeSize, n+cubeSize, n); // XY plane
    DrawRect(n,n,7-n, n+cubeSize, n+cubeSize, 7-n); // XY plane
    cubeSize -= 2;
    delay(128);
  }
}

//void DrawCube(int2_t x0, int2_t y0, int2_t z0, int2_t cubeSize)
//{
//  for (int8_t c=0; c<cubeSize; c++) {
//    DrawFront(x0+x,y0+c,z0+c, cubeSize);
//    delay(64);
//  }  
//}

void NormalState()
{
  int8_t n = 0;
  int8_t cubeSize=7;
  DrawRect(n,n,n, n, n+cubeSize, n+cubeSize); // YZ plane
  DrawRect(7-n,n,n, 7-n, n+cubeSize, n+cubeSize); // YZ plane
  DrawRect(n,n,n, n+cubeSize, n+cubeSize, n); // XY plane
  DrawRect(n,n,7-n, n+cubeSize, n+cubeSize, 7-n); // XY plane
}

void BumpRight()
{
  for (byte f=0; f<5; f++)
  {
    switch (f) {
    case 0: 
      DrawRect(7,0,0, 7,7,7);  
      break;
    case 1: 
      EraseRect(7,1,1, 7,6,6); 
      DrawRect(6,1,1, 6,6,6); 
      break;
    case 2: 
      EraseRect(6,2,2, 6,5,5); 
      DrawRect(5,2,2, 5,5,5);  
      break;
    case 3: 
      EraseRect(5,2,2, 5,5,5); 
      DrawRect(6,1,1, 6,6,6);  
      break;
    case 4: 
      EraseRect(6,1,1, 6,6,6);  
      DrawRect(7,0,0, 7,7,7);  
      break;
    }  
    delay(64);
  }
}


void Wiper()
{
  int dly = 32;
  for (int8_t y=0; y<8; y++) { DrawLine3(0,0, 7,y, 0); delay(dly); EraseLine3(0,0, 7,y, 0); }
  for (int8_t x=7; x>=0; x--){ DrawLine3(0,0, x,7, 0); delay(dly); EraseLine3(0,0, x,7, 0); }
  for (int8_t x=0; x<8; x++){ DrawLine3(0,0, x,7, 0); delay(dly); EraseLine3(0,0, x,7, 0); }
  for (int8_t y=7; y>=0; y--) { DrawLine3(0,0, 7,y, 0); delay(dly); EraseLine3(0,0, 7,y, 0); }
}


void LineTest()
{
  DrawLine3(0,0, 7,0, 0);
  DrawLine3(0,7, 0,0, 1);
  DrawLine3(0,0, 7,7, 2);
  DrawLine3(0,0, 4,7, 3);

  DrawLine3(7,0, 0,0, 4);
  DrawLine3(7,0, 0,4, 5);
  DrawLine3(7,0, 0,7, 6);
  DrawLine3(7,0, 4,7, 7);
}


void DropFromCenter()
{
  for (int8_t z=4; z>=0; z--)
  {
    EraseRect(3,3,z+1, 4,4,z+1);
    DrawRect(3,3,z, 4,4,z);
    delay(64);
  }
}

void SpreadFromCenter(int8_t z)
{
  for (int8_t a=0; a<3; a++)
  {
    DrawRect(2-a, 2-a, z, 5+a, 5+a, z);
    delay(64);
  }
}

void RaiseCorners()
{
  for (int8_t z=0; z<8; z++)
  {
    SetDot(0,0,z);
    SetDot(0,7,z);
    SetDot(7,0,z);
    SetDot(7,7,z);
    delay(64);
  }
}

void ZipTop()
{
  for (int8_t a=0; a<8; a++)
  {
    SetDot(a,0,7);
    SetDot(7-a,7,7);
    SetDot(7,a,7);
    SetDot(0,7-a,7);
    delay(64);
  }
}

void CollapseToFloor()
{
  for (int8_t z=7; z>0; z--)
  {
    EraseRect(0,0,z, 7,7,z);
    delay(64);
  }
}

void RaiseSeaLevel()
{
  for (int8_t z=0; z<5; z++)
  {
    EraseRect(0,0,z, 7,7,z);
    DrawRect(0,0,z+1, 7,7,z+1);
    delay(64);
  }
}


void DrawSine(int8_t offset, int8_t y)
{
  for (int8_t x=0; x<8; x++)
  {
    SetDot(x, y, sineArray[ (offset+x) % sineMaxIndex ]);
  }
}

void RippleFadeIn()
{
  for (int8_t x1=7; x1>=0; x1--)
  {
    int8_t index = 0;
    CubeAllOff();
    
    for (int8_t x=0; x<8; x++)
    {
      for (int8_t y=0; y<8; y++)
      {
        if (x<x1)
          SetDot(x, y, 5);
        else
          SetDot(x, y, sineArray[ index ]);
      }
      index++;
    }
    delay(32);
  }
}


void RippleToRight()
{
//  for (int8_t index=0; index < sineMaxIndex ; index++)
//  {
//    Serial.print("index="); Serial.print(index);
//    Serial.print(" sine="); Serial.println(sineArray[ index ]);
//  }
  
  for (byte n=0; n<2; n++) // repeat animation n times
  {
    for (byte offset=0; offset<sineMaxIndex; offset++)
    {
      CubeAllOff();
      for (int8_t y=0; y<8; y++)
      {
        DrawSine(offset, y); 
      }
      delay(32);
    }
  }
}
  

void CenterDiagonals()
{
//  Bresenham3D(0,0,0, 7,7,7); // FrontBottomLeft - BackRightTop
//  Bresenham3D(7,0,0, 0,7,7); // FrontBottomRight - BackLeftTop

//  Bresenham3D(0,0,7, 7,7,0);  // FrontTopLeft - BackRightBottom
//  Bresenham3D(7,0,7, 0,7,0);  // FrontTopRight - BackLeftBottom
}


void FollowLine(int8_t x0, int8_t y0, int8_t z0, int8_t dx, int8_t dy, int8_t dz)
{
  for (int8_t n=0; n<8; n++)
  {
    SetDot(x0,y0,z0);
    delay(64);
    ClearDot(x0,y0,z0);
    x0 = x0 + dx;
    y0 = y0 + dy;
    z0 =z0 + dz;
  }
}

void EdgeBurst()
{
  for (int8_t n=0; n<8; n++)
  {
    DrawLine3D(n,7,0, 0,7-n,0);
    DrawLine3D(0,7-n,0, 0,7,n);
    DrawLine3D(0,7,n, n,7,0);
    delay(64);
    EraseLine3D(n,7,0, 0,7-n,0);
    EraseLine3D(0,7-n,0, 0,7,n);
    EraseLine3D(0,7,n, n,7,0);
  }

  for (int8_t n=7; n>=0; n--)
  {
    DrawLine3D(n,7,0, 0,7-n,0);
    DrawLine3D(0,7-n,0, 0,7,n);
    DrawLine3D(0,7,n, n,7,0);
    delay(64);
    EraseLine3D(n,7,0, 0,7-n,0);
    EraseLine3D(0,7-n,0, 0,7,n);
    EraseLine3D(0,7,n, n,7,0);
  }
}

void EdgeBurst2(int8_t corner)
{
  for (int8_t dir=0; dir<2; dir++)
  {
    for (int8_t n=0; n<8; n++)
    {
      int8_t up = (dir==0) ? n : 7-n;
      int8_t down = (dir==0) ? 7-up : n;

      for (int8_t mode=1; mode>=0; mode--)
      {
        switch (corner)
        {
        case 0:
          //-- Bottom Left --      
          CalcLine3D(up,7,0, 0,down,0, mode);
          CalcLine3D(0,down,0, 0,7,up, mode);
          CalcLine3D(0,7,up, up,7,0, mode);
          break;
  
        case 1:
          //-- Bottom Right --
          CalcLine3D(down,7,0, 7,down,0, mode);
          CalcLine3D(7,down,0, 7,7,up, mode);
          CalcLine3D(7,7,up, down,7,0, mode);
          break;
        
        case 2:
        //-- Front Right
        CalcLine3D(down,0,0, 7,up,0, mode);
        CalcLine3D(7,up,0, 7,0,up, mode);
        CalcLine3D(7,0,up, down,0,0, mode);
        break;
        
      case 3:
        //-- Front Left
        CalcLine3D(up,0,0, 0,up,0, mode);
        CalcLine3D(0,up,0, 0,0,up, mode);
        CalcLine3D(0,0,up, up,0,0, mode);
        break;
        }
        if (mode==1) delay(64);
      }
    }
  }
}

void EdgesRandom()
{
  int8_t x, y, z;
  while (true)
  {
    x += -1 + random(0,3);
    y += -1 + random(0,3);
    z += -1 + random(0,3);
    if (x<0) x=7; if (x>7)x=0;
    if (y<0) y=7; if (y>7)y=0;
    if (z<0) z=7; if (z>7)z=0;
    DrawLine3D(x,7,0, 0,y,0);
    DrawLine3D(0,y,0, 0,7,z);
    DrawLine3D(0,7,z, x,7,0);
    delay(64);
    EraseLine3D(x,7,0, 0,y,0);
    EraseLine3D(0,y,0, 0,7,z);
    EraseLine3D(0,7,z, x,7,0);
  }
}

void Fans()
{
  // Fan out
  for (int8_t dx=0; dx<4; dx++)
  {
    for (int8_t y=0; y<8; y++)
    {
      DrawLine3D(4,y,7, 4+dx,y,0);
      DrawLine3D(3,y,7, 3-dx,y,0);
    }
    delay(64);
    if (dx==3) delay(128);
    CubeAllOff();//    for (int8_t y=0; y<8; y++)
//    {
//      EraseLine3D(4,y,7, 4+dx,y,0);
//      EraseLine3D(3,y,7, 3-dx,y,0);
//    }
  }

  // Fan in
  for (int8_t dx=3; dx>=0; dx--)
  {
    for (int8_t y=0; y<8; y++)
    {
      DrawLine3D(4,y,7, 4+dx,y,0);
      DrawLine3D(3,y,7, 3-dx,y,0);
    }
    delay(64);
    if (dx==0) delay(128);
    CubeAllOff();
//    for (int8_t y=0; y<8; y++)
//    {
//      EraseLine3D(4,y,7, 4+dx,y,0);
//      EraseLine3D(3,y,7, 3-dx,y,0);
//    }
  }
}

void DotToRect() // Spawn a rect from bottom left corner
{
  for (int8_t n=0; n<8; n++)
  {
    SetDot(n,7, 0);
    SetDot(0,7-n, 0);
    delay(64);
  }

  for (int8_t n=0; n<8; n++)
  {
    SetDot(7,7-n, 0);
    SetDot(n,0, 0);
    delay(64);
  }
}

void FillBottom()
{
  for (int8_t x=0; x<8; x++)
  {
    DrawLine3D(x,0,0, x,7,0);
    delay(64);
  }
}

void FoldUp()
{
  for (int8_t n=0; n<9; n++)
  {
    int8_t x = quarterArc[n][0];
    int8_t z = quarterArc[n][1];

    for (int8_t y=0; y<8; y++)
      DrawLine3D(0,y,0, x,y,z);

    delay(64);

    if (n>0 && n<8) {
      for (int8_t y=0; y<8; y++)
        EraseLine3D(0,y,0, x,y,z);
    }

    DrawRect(0,0,0, 7,7,0); // Bottom XY plane
  }
}

void FoldFromLeft()
{
  for (int8_t n=8; n>=0; n--)
  {
    int8_t x = quarterArc[n][0];
    int8_t z = 7 - quarterArc[n][1];

    for (int8_t y=0; y<8; y++)
      DrawLine3D(0,y,7, x,y,z);

    delay(64);

    if (n>0 && n<8) {
      for (int8_t y=0; y<8; y++)
        EraseLine3D(0,y,7, x,y,z);
    }

    DrawRect(0,0,0, 7,7,0); // Bottom XY plane
    DrawRect(0,0,0, 0,7,7); // Left Wall
  }
}


void FoldTopToRight()
{
  for (int8_t n=0; n<9; n++)
  {
    int8_t x = 7 - quarterArc[n][0];
    int8_t z = 7 - quarterArc[n][1];

    for (int8_t y=0; y<8; y++)
      DrawLine3D(7,y,7, x,y,z);

    delay(64);

    if (n>0 && n<8) {
      for (int8_t y=0; y<8; y++)
        EraseLine3D(7,y,7, x,y,z);
    }

    DrawRect(0,0,0, 7,7,0); // Bottom XY plane
    DrawRect(0,0,0, 0,7,7); // Left Wall
    DrawRect(0,0,7, 7,7,7); // Top XY plane
  }
}

void PinWheel(int8_t y)
{
  for (int8_t n=0; n<8; n++)
  {
    DrawLine3D(0,y,n, 7,y,7-n);
    delay(64);
  }  

  for (int8_t n=0; n<8; n++)
  {
    DrawLine3D(n,y,7, 7-n,y,0);
    delay(64);
  }  
}

void DrawCircle(int8_t z)
{
  for (int8_t n=0; n<20; n++)
  {
    SetDot(circle[n][0], circle[n][1], z);
    delay(128);
  }
}

void SnakeSpiralDown()
{
  for (int8_t z=0; z<8; z++)
  {
    for (int8_t n=0; n<20; n++)
    {
      if (z>0) ClearDot(circle[n][0], circle[n][1], 8-z);
      SetDot(circle[n][0], circle[n][1], 7-z);
      delay(16);
    }
  }
}
