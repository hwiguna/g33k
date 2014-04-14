// Keyboard Matrix reader using 4 analog pins
// by Hari Wiguna 2014
// Circuit and this code at https://github.com/hwiguna/g33k

byte rowPins[] = {A0,A1,A2,A3};
byte rowChars[][5] = {
  {'1','2','3','A',' '},
  {'4','5','6','B',' '},
  {'7','8','9','C',' '},
  {'*','0','#','D',' '}
};
char lastChar = ' ';

void setup() {
  // Enable pullup resistor on A0..A3 so we won't get random values when no keys are pressed.
  for (byte i=0; i<4; i++)
    digitalWrite(rowPins[i],HIGH);

  // initialize the serial communication:
  Serial.begin(9600);
}

// Translate analog 0..1023 values to 0..4
// I don't use map() function because I want complete control over where the thresholds are.
// These thresholds are chosen by averaging values for each column and then finding the mid points between them.
byte AnalogToIndex(int a) {
  return a < 360 ? 0 : a < 548 ? 1 : a < 734 ? 2 : a < 920 ? 3 : 4;
}

void loop() {
  byte value = ' ';
  int rawValues[4];
  for (byte row=0; row<4; row++) {
    int rawValue = analogRead( rowPins[row] );
    byte columnIndex = AnalogToIndex( rawValue );
    if (columnIndex<4) {
      value = rowChars[row][columnIndex];
      break;
    }
  }

  if (value != lastChar ) {
    Serial.write(value); Serial.println();
    lastChar = value;
  }

  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(20);
}

