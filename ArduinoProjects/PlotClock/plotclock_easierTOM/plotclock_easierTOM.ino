// Plotclock
// cc - by Johannes Heberlein 2014
// v 1.02
// thingiverse.com/joo   wiki.fablab-nuernberg.de
// units: mm; microseconds; radians
// origin: bottom left of drawing surface
// time library see http://playground.arduino.cc/Code/time 
// RTC  library see http://playground.arduino.cc/Code/time 
//               or http://www.pjrc.com/teensy/td_libs_DS1307RTC.html  
// Change log:
// 1.01  Release by joo at https://github.com/9a/plotclock
// 1.02  Additional features implemented by Dave:
//       - added ability to calibrate servofaktor seperately for left and right servos
//       - added code to support DS1307, DS1337 and DS3231 real time clock chips
//       - see http://www.pjrc.com/teensy/td_libs_DS1307RTC.html for how to hook up the real time clock 

// delete or mark the next line as comment if you don't need these
#define CALIBRATION      // enable calibration mode
//#define REALTIMECLOCK    // enable real time clock

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
#define SERVOLEFTNULL 2080 //Hari:2200. Orig:2250 pointing left pos. larger# = COUNTER clockwise
#define SERVORIGHTNULL 900 //Hari:600.  Orig:920 Smaller# = clockwise

// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
#define SERVOFAKTORLEFT 570 // 650. vertical-ness of left servo.  Larger # = more clockwise
#define SERVOFAKTORRIGHT 500 // 650. vertical-ness of right servo. Larger # = more COUNTER clockwise

#define SERVOPINLIFT  2
#define SERVOPINLEFT  3
#define SERVOPINRIGHT 4

// lift positions of lifting servo
#define LIFT0 1100 // Hari:1220. Orig:1080 on drawing surface -- Larger# = closer to surface
#define LIFT1 1050  // Hari:1055. Orig:925  between numbers (park pen inside sweeper)
#define LIFT2 600  // Hari:800.  Orig:725  lift above the sweeper

// speed of lifting arm, higher is slower
#define LIFTSPEED 1500

// length of arms
#define L1 35
#define L2 55.1
#define L3 13.2

// origin points of left and right servo 
#define O1X 22
#define O1Y -25
#define O2X 47
#define O2Y -25

#include <Time.h> // see http://playground.arduino.cc/Code/time 
#include <Servo.h>

int Left0 = 2080; //SERVOLEFTNULL;
int Right0 = 900; //SERVORIGHTNULL;
int Left90 = 570; //SERVOFAKTORLEFT;
int Right90 = 550; //SERVOFAKTORRIGHT;

int lift0 = LIFT0;
int lift1 = LIFT1;
int lift2 = LIFT2;

int Mode = 2;

double parkX = 74; //74.2; 
double parkY = 45; //47.5; Smaller# = closer to servo

double midX = parkX / 2;
double midY = parkY;

#ifdef REALTIMECLOCK
// for instructions on how to hook up a real time clock,
// see here -> http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
// DS1307RTC works with the DS1307, DS1337 and DS3231 real time clock chips.
// Please run the SetTime example to initialize the time on new RTC chips and begin running.

  #include <Wire.h>
  #include <DS1307RTC.h> // see http://playground.arduino.cc/Code/time    
#endif

Servo servo1;  // 
Servo servo2;  // 
Servo servo3;  // 

int servoLift = LIFT2; // Initially set  orig:1500;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


volatile double lastX = 75;
volatile double lastY = 47.5;

int last_min = 0;

void DisplayConfig() 
{
  Serial.println();
  Serial.print("l)eft 0   = ");  Serial.println(Left0);
  Serial.print("r)ight 0  = ");  Serial.println(Right0);
  Serial.print("L)eft 90  = ");  Serial.println(Left90);
  Serial.print("R)ight 90 = ");  Serial.println(Right90);
  Serial.print("Lift (0)(1)(2) = ");  Serial.print(lift0); Serial.print(","); Serial.print(lift1); Serial.print(","); Serial.println(lift2);
  Serial.print("park(x), park(y) = ");  Serial.print(parkX); Serial.print(","); Serial.println(parkY);
  Serial.print("m)ode = ");      Serial.println(Mode);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void HandleSerialCommands()
{
  if (stringComplete) {
    Serial.println("received: '" + inputString +"'");
    byte equalPos = inputString.indexOf("=");
    if (equalPos != -1) {
      String cmd = inputString.substring(0,equalPos);
      String val = inputString.substring(equalPos+1, inputString.length()-1);
      ProcessCommand(cmd, val);
    }
    inputString = "";
    stringComplete = false;
  }  
}

void WriteConfig()
{
  
}

void ProcessCommand(String cmd, String val) {
  Serial.print("cmd="); Serial.println(cmd);
  Serial.print("val="); Serial.println(val);
  
  boolean isBadCmd = false;
  int value = val.toInt();
  switch (cmd[0]) {
    case 'l': Serial.println("left 0");   Left0   = value; break;
    case 'L': Serial.println("LEFT 90");  Left90  = value; break;
    case 'r': Serial.println("right 0");  Right0  = value; break;
    case 'R': Serial.println("RIGHT 90"); Right90 = value; break;

    case 'x': Serial.println("ParkX"); parkX = value; break;
    case 'y': Serial.println("ParkY"); parkY = value; break;

    case '0': Serial.println("Lift 0"); lift0 = value; break;
    case '1': Serial.println("Lift 1"); lift1 = value; break;
    case '2': Serial.println("Lift 2"); lift2 = value; break;

    case 'm': Serial.println("Mode");     Mode = value; break;
    case 'w': Serial.println("Write"); WriteConfig(); break;
    default:
      isBadCmd = true;
      break;
  }
  
  if (!isBadCmd) {
    DisplayConfig();
  }
}

void setup() 
{ 
  Serial.begin(9600);

#ifdef REALTIMECLOCK
  //while (!Serial) { ; } // wait for serial port to connect. Needed for Leonardo only

  // Set current time only the first to values, hh,mm are needed  
  tmElements_t tm;
  if (RTC.read(tm)) 
  {
    setTime(tm.Hour,tm.Minute,tm.Second,tm.Day,tm.Month,tm.Year);
    Serial.println("DS1307 time is set OK.");
  } 
  else 
  {
    if (RTC.chipPresent())
    {
      Serial.println("DS1307 is stopped.  Please run the SetTime example to initialize the time and begin running.");
    } 
    else 
    {
      Serial.println("DS1307 read error!  Please check the circuitry.");
    } 
    // Set current time only the first to values, hh,mm are needed
    setTime(19,38,0,0,0,0);
  }
#else  
  // Set current time only the first to values, hh,mm are needed
  setTime(10,45,0,0,0,0);
#endif

  DisplayConfig();

  //-- Set initial positions BEFORE attaching servos --
  lift(2);
  drawTo(parkX, parkY);
  servo1.attach(SERVOPINLIFT);  //  lifting servo
  servo2.attach(SERVOPINLEFT);  //  left servo
  servo3.attach(SERVOPINRIGHT);  //  right servo
  delay(1000); // Wait a second to verify that we're above the eraser well
} 

void Reset()
{
  //-- verify that the pen is parked inside the eraser well --
  lift(1);
  delay(2000);

  //-- Move pen to middle of drawing surface --
  lift(2); // Lift pen above eraser well
  drawTo(midX, midY); // Move to drawing area
  lift(1);  delay(2000); // Pen should be just above the surface now
  lift(0);  delay(2000); // Pen should be ON the surface now

  //-- Park pen again --
  lift(2);
  drawTo(parkX, parkY);
  lift(1);
  delay(2000);
}

void loop() 
{ 
  HandleSerialCommands();
  
  switch (Mode) {
    case 0: CalibrationMode(); break;
    case 1: Reset();break;
    case 2: ClockMode(); break;
  }
}

void CalibrationMode()
{
//  drawTo(parkX, parkY);
//  lift(0);  delay(3000); // 0 = pen is on writing surface
//  lift(1);  delay(1000); // 1 = lift pen (height when pen is parked in eraser well)
  lift(2);  delay(1000); // 2 = lift above eraser

  // Servohorns will have 90° between movements, parallel to x and y axis
  drawTo(-3, 29.2);
  delay(500);
  drawTo(74.1, 28);
  delay(500);
}

void ClockMode()
{
  //if (last_min != minute()) 
  {
    //-- We release servos every cycle to keep them from buzzing, so re-attach them before drawing --
    if (!servo1.attached()) servo1.attach(SERVOPINLIFT);
    if (!servo2.attached()) servo2.attach(SERVOPINLEFT);
    if (!servo3.attached()) servo3.attach(SERVOPINRIGHT);

    int currentHour = hour();
    int hour1 = currentHour/10;
    int hour2 = currentHour % 10;

    int currentMin = minute();
    int min1 = currentMin/10;
    int min2 = currentMin % 10;

    //-- Erase --
    number(3, 3, 111, 1);   // 111 = Erase

    //-- Hours --
    number(5, 25,  hour1, 0.9);  // ?h:mm
    number(19, 25, hour2, 0.9);  // h?:mm

    //-- Colon --
    number(28, 25, 11, 0.9); // 11=Colon

    //-- Minutes --
    number(34, 25, min1, 0.9); // hh:?m
    number(48, 25, min2, 0.9); // hh:m?

    //-- Park Pen --
    lift(2); // Lift above the eraser
    drawTo(parkX, parkY); // Go to eraser park position
    lift(1); // Insert pen in eraser well
    
    last_min = currentMin;

    //-- Release servos --
    delay(1000);
    servo1.detach();
    servo2.detach();
    servo3.detach();
    
    delay(10000); // demo mode :-) refresh every 10 seconds.
  }
}

// Writing numeral with bx by being the bottom left originpoint. Scale 1 equals a 20 mm high font.
// The structure follows this principle: move to first startpoint of the numeral, lift down, draw numeral, lift up
void number(float bx, float by, int num, float scale) {

  switch (num) {

  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(0);
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
    lift(1);
    break;

  case 1:
    drawTo(bx + 3 * scale, by + 15 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(1);
    break;

  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(0);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    lift(1);
    break;

  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    lift(1);
    break;

  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(1);
    break;

  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(1);
    break;

  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(1);
    break;

  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;

  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(1);
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(1);
    break;

  case 111: // Erase
    lift(1);
    drawTo(70, 46);
    drawTo(65, 43);

    drawTo(65, 49);
    drawTo(5, 49);
    drawTo(5, 45);
    drawTo(65, 45);
    drawTo(65, 40);

    drawTo(5, 40);
    drawTo(5, 35);
    drawTo(65, 35);
    drawTo(65, 30);

    drawTo(5, 30);
    drawTo(5, 25);
    drawTo(65, 25);
    drawTo(65, 20);

    drawTo(5, 20);
    drawTo(60, 44);

    drawTo(parkX, parkY);
    delay(2000);
    lift(2);

    break;

  case 11: // Colon
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    break;

  }
}


void lift(char lift) {
  int desiredServoPos;
  switch (lift) {
    case 0: desiredServoPos = lift0; break;
    case 1: desiredServoPos = lift1; break;
    case 2: desiredServoPos = lift2; break;
  }

  if (servoLift >= desiredServoPos) {
    while (servoLift >= desiredServoPos) {
      servoLift--;
      servo1.writeMicroseconds(servoLift);
      delayMicroseconds(LIFTSPEED);
    }
  } 
  else {
    while (servoLift <= desiredServoPos) {
      servoLift++;
      servo1.writeMicroseconds(servoLift);				
      delayMicroseconds(LIFTSPEED);
    }
  }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) > ende);
}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(4 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}

double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); // 
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);

  servo2.writeMicroseconds(floor(((a2 + a1 - M_PI) * Left90) + Left0));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);

  servo3.writeMicroseconds(floor(((a1 - a2) * Right90) + Right0));
}





