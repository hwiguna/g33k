#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

void LcdWriteData(byte dat)
{
digitalWrite(DC, HIGH); //DC pin is high for data
digitalWrite(CE, LOW);
shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
digitalWrite(CE, HIGH);
}

void LcdWriteCmd(byte cmd)
{
digitalWrite(DC, LOW); //DC pin is low for commands
digitalWrite(CE, LOW);
shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
digitalWrite(CE, HIGH);
}

void setup()
{
pinMode(RST, OUTPUT);
pinMode(CE, OUTPUT);
pinMode(DC, OUTPUT);
pinMode(DIN, OUTPUT);
pinMode(CLK, OUTPUT);
digitalWrite(RST, LOW);
digitalWrite(RST, HIGH); LcdWriteCmd(0x21); // LCD extended commands
LcdWriteCmd(0xa7); // set LCD Vop (contrast) B8
LcdWriteCmd(0x04); // set temp coefficent
LcdWriteCmd(0x14); // LCD bias mode 1:40
LcdWriteCmd(0x20); // LCD basic commands
//LcdWriteCmd(0x09); // LCD all segments on
//LcdWriteCmd(0x00); // LCD all segments off
LcdWriteCmd(0x0C); // LCD normal video
//LcdWriteData(0x55);

//LcdWriteData(0x55);
LcdWriteData(0xAA);
}

void loop()
{
}
