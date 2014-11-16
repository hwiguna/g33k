const byte RCLK = 11;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte SRCLK = 12;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte SER = 13;    // Serial input, read in on positive edge of SRCLK (Blue wire)

void setup() {
  // put your setup code here, to run once:
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(SER,OUTPUT);
}

void loop() {
  byte byteHi = B11000000;
  byte byteLo = B00000001;
  
  // set RCLK low; wait till we transmit the byte, and they moving it high will output the data
  digitalWrite(RCLK, LOW);

  // shift out the bits (MSBFIRST = most significant bit first)
  shiftOut(SER, SRCLK, LSBFIRST, byteLo);
  shiftOut(SER, SRCLK, LSBFIRST, byteHi);

  // send shift register data to the storage register
  digitalWrite(RCLK, HIGH);
  
  // catch our breath before repeating
  delay(1000);
}
