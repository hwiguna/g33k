const byte RCLK = 11;   // Register Clock: Positive edge triggers shift register to output (White wire)
const byte SRCLK = 12;  // Shift Register Clock: Positive edge triggers SER input into shift register (Yellow wire)
const byte SER = 13;    // Serial input, read in on positive edge of SRCLK (Blue wire)

int twoBytes;

void setup() {
  // put your setup code here, to run once:
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(SER,OUTPUT);
}

void loop() {
  for (byte i=0; i<16; i++) {
    twoBytes = 0;
    Plot(i-1,0); Plot(i,1); 
    Plot(15-i+1,0); Plot(15-i,1); 
    Refresh();
    delay(25);
  }
}

void Plot(byte index, byte value) {
  if (index>=0 && index<16)
    if (value)
      bitSet(twoBytes, index);
      else
    bitClear(twoBytes, index);
}

void Refresh()
{
  twoBytes = ~twoBytes;

  // set RCLK low; wait till we transmit the byte, and they moving it high will output the data
  digitalWrite(RCLK, LOW);

  // shift out the bits (MSBFIRST = most significant bit first)
  shiftOut(SER, SRCLK, LSBFIRST, lowByte(twoBytes));
  shiftOut(SER, SRCLK, LSBFIRST, highByte(twoBytes));

  // send shift register data to the storage register
  digitalWrite(RCLK, HIGH);

}
