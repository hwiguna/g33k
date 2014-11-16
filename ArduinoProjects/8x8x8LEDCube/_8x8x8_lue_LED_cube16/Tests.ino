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

void BottomCorner()
{
  for (int8_t x=0; x<1; x++) {
    for (int8_t y=7; y<8; y++) {
      SetDot(x,y,1); 
    }
  }
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



