//== 3D calculations ==

float ratio;
u8g_uint_t shift;
u8g_uint_t x0, y0;
bool blocked;

void SetupDrawing()
{
  u8g.setRot180();  // flip screen
  screenWidth = u8g.getWidth();
  screenHeight = u8g.getHeight();
  x0 = screenHalfWidth = screenWidth / 2;
  y0 = screenHalfHeight = screenHeight / 2;
  hInset = screenWidth / 7;
  ratio = 1.0 * screenHalfHeight / screenHalfWidth;
}

void XToCorners(u8g_uint_t x, Point* points) {
  u8g_uint_t y = (u8g_uint_t)(1.0 * x * ratio);
  points[0].Set(x0 - x, y0 - y); // 0 = top left
  points[1].Set(x0 + x, y0 - y); // 1 = top right
  points[2].Set(x0 + x, y0 + y); // 2 = bottom right
  points[3].Set(x0 - x, y0 + y); // 3 = bottom left
}

void DrawFrontLeftWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, outs[0].Y, ins[0].X, ins[0].Y);
  u8g.drawLine(ins[0].X, ins[0].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, outs[3].X, outs[3].Y);
}

void DrawFrontRightWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[1].X, outs[1].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, outs[2].X, outs[2].Y);
}

void DrawBackLeftWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, ins[0].Y, ins[0].X, ins[0].Y);
  u8g.drawLine(ins[0].X, ins[0].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, outs[3].X, ins[3].Y);
}

void DrawBackRightWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[1].X, ins[1].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, outs[2].X, ins[2].Y);
}

void DrawFrontWall(Point* outs, Point* ins)
{
  u8g.drawLine(outs[0].X, outs[0].Y, outs[1].X, outs[1].Y);
  u8g.drawLine(outs[1].X, outs[1].Y, outs[2].X, outs[2].Y);
  u8g.drawLine(outs[2].X, outs[2].Y, outs[3].X, outs[3].Y);
  u8g.drawLine(outs[3].X, outs[3].Y, outs[0].X, outs[0].Y);
}

void DrawBackWall(Point* outs, Point* ins)
{
  u8g.drawLine(ins[0].X, ins[0].Y, ins[1].X, ins[1].Y);
  u8g.drawLine(ins[1].X, ins[1].Y, ins[2].X, ins[2].Y);
  u8g.drawLine(ins[2].X, ins[2].Y, ins[3].X, ins[3].Y);
  u8g.drawLine(ins[3].X, ins[3].Y, ins[0].X, ins[0].Y);
}

//void DebugWalls(byte depth, byte col, byte row)
//{
//  if (millis() > timeToDebug)
//  {
//    Serial.println("--------------------------");
//    Debug("depth", depth);
//    Debug("col", col);
//    Debug("row", row);
//    Debug("hasFrontLeftWall", hasFrontLeftWall);
//    Debug("hasFrontWall", hasFrontWall);
//    Debug("hasFrontRightWall", hasFrontRightWall);
//    Debug("hasBackLeftWall", hasBackLeftWall);
//    Debug("hasBackWall", hasBackWall);
//    Debug("hasBackRightWall", hasBackRightWall);
//    timeToDebug = millis() + 2000;
//  }
//}

void TurnRightAnimation(Point* outs, Point* ins)
{
  for (byte i = 0; i < 4; i++) {
    outs[i].X = max(0, outs[i].X -   hShift);
    ins[i].X = max(0,ins[i].X -   hShift);
  }
}

void TurnLeftAnimation(Point* outs, Point* ins)
{
  for (byte i = 0; i < 4; i++) {
    outs[i].X = min(screenWidth,outs[i].X + hShift);
    ins[i].X = min(screenWidth,ins[i].X +  hShift);
  }
}

void BumpAnimation(byte depth, Point* outs, Point* ins)
{
  //if (depth==0) Buzz();
  int offset = vShift==0 ? -2 : +2;
  for (byte i = 0; i < 4; i++) {
    outs[i].X = min(screenWidth-1,max(0,outs[i].X - offset));
    ins[i].X = min(screenWidth-1,max(0,ins[i].X -  offset));
  }
//  for (byte i = 0; i < 4; i++) {
//    outs[i].Y = min(screenHeight-1,max(0,outs[i].Y - offset));
//    ins[i].Y = min(screenHeight-1,max(0,ins[i].Y -  offset));
//  }
}

void DrawWalls(byte depth, byte col, byte row)
{
  Point outs[4], ins[4];
  XToCorners(screenHalfWidth - hInset * depth       + (depth == 0 ? 0 : zoom), outs);
  XToCorners(screenHalfWidth - hInset * (depth + 1) + zoom, ins);

  if (youRotDir > 0) TurnRightAnimation(outs, ins);
  if (youRotDir < 0) TurnLeftAnimation(outs, ins);
  if (bumpCount > 0) BumpAnimation(depth,outs,ins);

  if (youDir == 0) LookNorth(row - depth, col);
  if (youDir == 1) LookEast(row, col + depth);
  if (youDir == 2) LookSouth(row + depth, col);
  if (youDir == 3) LookWest(row, col - depth);
  //DebugWalls(depth,row,col);

  if (hasFrontWall)
    DrawFrontWall(outs, ins);
  else
  {
    if (hasBackWall) DrawBackWall(outs, ins);

    if (hasFrontLeftWall) DrawFrontLeftWall(outs, ins);
    else if (hasBackLeftWall) DrawBackLeftWall(outs, ins);

    if (hasFrontRightWall) DrawFrontRightWall(outs, ins);
    else if (hasBackRightWall) DrawBackRightWall(outs, ins);
  }
}

void DrawMaze()
{
  u8g.drawFrame(0, 0, screenWidth, screenHeight);

  blocked = false; // Assume there's nothing in front of us
  for (byte depth = 0; depth < 3; depth++)
    if (!blocked) {
      DrawWalls(depth, youCol, youRow);
      blocked = hasFrontWall || hasBackWall;
    }
}

