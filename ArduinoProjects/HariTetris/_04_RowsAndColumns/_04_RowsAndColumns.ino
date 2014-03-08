const byte Row_RCLK = 11;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Row_SRCLK = 12;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Row_SER = 13;    // Serial input, read in on positive edge of SRCLK (Blue wire)

const byte Col_RCLK =5;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte Col_SRCLK = 6;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte Col_SER = 7;    // Serial input, read in on positive edge of SRCLK (Blue wire)

int twoBytes;

void setup() {
  // put your setup code here, to run once:
  pinMode(Row_RCLK,OUTPUT);
  pinMode(Row_SRCLK,OUTPUT);
  pinMode(Row_SER,OUTPUT);

  pinMode(Col_RCLK,OUTPUT);
  pinMode(Col_SRCLK,OUTPUT);
  pinMode(Col_SER,OUTPUT);
}

void loop() {
  for (byte r=0; r<16; r++) {
    twoBytes = 0;
    Plot(15-r+1,0); Plot(15-r,1); 
    twoBytes = ~twoBytes; // Rows need to be pulled to negative.  So turn ONEs into LOWs
    WriteRow( highByte(twoBytes), lowByte(twoBytes) );

    for (byte i=0; i<16; i++) {
      twoBytes = 0;
      Plot(i-1,0); Plot(i,1); 
      Plot(15-i+1,0); Plot(15-i,1); 
      WriteCol( highByte(twoBytes), lowByte(twoBytes) );
      delay(25);
    }
  }
}

void Plot(byte index, byte value) {
  if (index>=0 && index<16)
    if (value)
      bitSet(twoBytes, index);
      else
    bitClear(twoBytes, index);
}

void WriteRow(byte hiByte, byte loByte) {
  digitalWrite(Row_RCLK, LOW);
  shiftOut(Row_SER, Row_SRCLK, LSBFIRST, loByte);
  shiftOut(Row_SER, Row_SRCLK, LSBFIRST, hiByte);
  digitalWrite(Row_RCLK, HIGH);
};

void WriteCol(byte hiByte, byte loByte) {
  digitalWrite(Col_RCLK, LOW);
  shiftOut(Col_SER, Col_SRCLK, LSBFIRST, loByte);
  shiftOut(Col_SER, Col_SRCLK, LSBFIRST, hiByte);
  digitalWrite(Col_RCLK, HIGH);
};
