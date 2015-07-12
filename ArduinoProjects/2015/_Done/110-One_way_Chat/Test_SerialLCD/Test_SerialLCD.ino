
int kount = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }  

// NewHaven display Contrast
Serial.write(0xFE); 
Serial.write(0x52);
Serial.write(40);
delay(1000);
// NewHaven display brightness
Serial.write(0xFE); 
Serial.write(0x53);
Serial.write(8);
delay(1000);

// Display baud
Serial.write(0xFE); 
Serial.write(0x71);
delay(2000);
}

void loop()
{
  // NewHaven display clear screen
  Serial.write(0xFE); 
  Serial.write(0x51);
  
  delay(100);
      Serial.print("Hellow ");
      Serial.print(kount++);
delay(1000);
}

