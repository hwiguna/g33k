#include <CapacitiveSensor.h>

// 8x8x8x Blue LED Cube
// by Hari Wiguna 2014
//
// v03 - blinks all 512
// v04 - more test patterns.  Uses TimerOne library.
// v06 - Using MsTimer2
// v07 - Don't turn off previous layer until the very last moment for brighter display
// v09 - Pedal to the metal, no timer libraries!
// v10 - Invert shift register output in DrawLayers() because we longer use transistors there.
// v11 - Add Capsense library
// v12 - Add two potentiometers on Analog 4 and 5
// v13 - Working on patterns
// v14 - Split code into multiple tabs, Flea Jump

//-- Shift Register pins --
int latchPin = 13; // Arduino D13 to IC pin 12 (ST_CP) -- White
int clockPin = 12; // Arduino D12 to IC pin 11 (SH_CP) -- Yelow
int dataPin  = 11; // Arduino D11 to IC pin 14 (DS) -- Blue

//-- Globals --
byte slomo = 0;
volatile int8_t cube[8][8]; // byte bits = X, 1st index=Y, 2nd index = Z
volatile int8_t gZ = 0;
int pot0; // Left Potentiometer (A4)
int pot1; // Right Potentiometer (A5)
int oldPot0;
int animSpeed; // Animation speed controlled by pot0
float pi = 3.14;
float pi2 = 6.28;
const int8_t sineMaxIndex = 32;
int8_t sineArray[sineMaxIndex];
int8_t quarterArc[][2] = {{7,0},{7,1},{7,2}, {6,4},{5,5},{4,6}, {2,7},{1,7},{0,7}};
int8_t circle[][2] = {
{2,7},{3,7},{4,7},{5,7}, {6,6},
{7,5},{7,4},{7,3},{7,2}, {6,1},
{5,0},{4,0},{3,0},{2,0}, {1,1},
{0,2},{0,3},{0,4},{0,5}, {1,6}};
int8_t arrow[] = {
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111110,
  B00111100,
  B00011000,
};
int8_t pathSquare[][2] = {
  {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0}, // Front
  {7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7}, // Right
  {6,7},{5,7},{4,7},{3,7},{2,7},{1,7},{0,7}, // Back
  {0,7},{0,6},{0,5},{0,4},{0,3},{0,2},{0,1}, // Right
};

int8_t pathSmallSquare[][2] = {
  {2,2},{3,2},{4,2},{5,2}, // Front
  {5,3},{5,4},{5,5}, // Right
  {4,5},{3,5},{2,5}, // Back
  {2,4},{2,3},{2,2}, // Right
};
int8_t pathSmallCircle[][2] = {
  {3,2},{4,2}, // Front
  {5,3},{5,4}, // Right
  {4,5},{3,5}, // Back
  {2,4},{2,3}, // Right
};

//-- CapSense --
CapacitiveSensor   cs_14_15 = CapacitiveSensor(14,15);
CapacitiveSensor   cs_14_16 = CapacitiveSensor(14,16);
CapacitiveSensor   cs_14_17 = CapacitiveSensor(14,17);

void setup(void) {
  SetupPins();
  SetupCapSense();
  Serial.begin(9600);
  PreComputes();
  CubeAllOff();
  //LineTest();
  
  //RunTests();
  SetupTimer();
  //for (byte n=0; n<3; n++) Wiper();
  //TestBresenham3D();
  //CenterDiagonals();
  //Pyramid3();
}

void loop(void) {
  //One_Pixel_Up_a_wall(7);
  //Line_Up_a_wall(1);
  //BottomUp();

  //CubeRightLeft();  //delay(1000);
  //CubeLeftRight();  //delay(1000);
  //CubeUp();  //delay(1000);
  //CubeDown();  //delay(1000);
  //CubeAllOn(); delay(2000);
  //CubeAllOff();

  //TestPattern2_Scan_one_layer(0);  //delay(1000);
  //TestPattern_scan_all_layers();  //delay(1000);
  //TestPattern4_Scan_one_wall();  delay(1000);
  //TestPattern5_swipe_wall_up();  //delay(1000);
  //CubeAllOn(); delay(1000);
  //BottomCorner();
  //LeftRight();
  //OneWall();  delay(1000);
  //LayerOn(0); delay(4000);

  //-- CapSense --
  long total1 =  cs_14_15.capacitiveSensor(30);
  long total2 =  cs_14_16.capacitiveSensor(30);
  long total3 =  cs_14_17.capacitiveSensor(30);
  //Serial.print(total1);                  // print sensor output 1
  //Serial.print("\t");
  //Serial.println(total2);
  if (total1>200) CubeLeftRight(); // Left touchpad
  if (total2>200) MainShow(); // Front touchpad
  if (total3>200) BumpRight(); //CubeRightLeft(); // Right touchpad

  pot0 = analogRead(A4);
  pot1 = analogRead(A5);

  animSpeed = map(pot0, 0,1023, 16,256);

  //CubeAllOff();
  //NormalState();
  //Pyramid3();
  //Fans();
  //EdgesRandom();
  //while (true) WallJump();
  //AnArrow();
  //while (true) AnimatedDot();
    //while (true) Tornado();
    /*
  FleaJump    (1, 7, 4, 1, 0); // front
  FleaJump    (1, 7, 3, 6, 1); // right
  FleaJumpBack(1, 7, 3, 6, 0); // back
  FleaJumpBack(1, 7, 4, 1, 1); // left
  */
    FleaJmp(1,1, 6,1, 4); // Front
    FleaJmp(6,1, 6,7, 3); // Right
    FleaJmp(6,7, 1,7, 3); // Back
    FleaJmp(1,7, 1,1, 4); // left
}

