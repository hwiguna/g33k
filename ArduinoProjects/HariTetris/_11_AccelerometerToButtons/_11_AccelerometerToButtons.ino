byte currentX = 6;
byte currentY = 6;
int xPrev = 0;
int yPrev = 0;

const int xSensor = A4; // x refers to game x, A4 is actually connected to accelerometer Y axis
const int ySensor= A5;  // Analog input pin that the potentiometer is attached to

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  int xValue = analogRead(xSensor);
  int yValue = analogRead(ySensor);
    
  int xDiff = xValue - xPrev;
  int yDiff = yValue - yPrev;
  xPrev = xValue;
  yPrev = yValue;
  
  const int yMax = 250; // Top-down = Rotate
  const int yMin = 175; // Top-up = Drop piece
  
  const int xMax = 390; // Right-down = Shift right
  const int xMin = 330; // Left-down = shift left
  
  int xOffset = 0;
  int yOffset = 0;
  String action="";
  if (yValue > yMax) action="Rotate";
  if (yValue < yMin) action="Drop";
  if (action=="") {
    if (xValue > xMax) action="-->";
    if (xValue < xMin) action="<--";
  }

  currentX =+ xOffset; // offsets are in accdelerometer axis, which is opposite of LED maxtrix axis.
  currentY =+ yOffset;

  Serial.print("("); 
  Serial.print(xValue); Serial.print(", "); 
  Serial.print(yValue); Serial.print(") Diff=("); 

  Serial.print(xDiff); Serial.print(", "); 
  Serial.print(yDiff); Serial.print(") Current=("); 

  Serial.print(currentX); Serial.print(", "); 
  Serial.print(currentY); Serial.print(" Action="); 

  Serial.print(action); Serial.println(); 

  delay(300);                     
}
