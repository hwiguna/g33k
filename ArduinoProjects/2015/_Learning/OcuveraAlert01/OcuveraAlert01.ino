
int inByte = 0;         // incoming serial byte

void setup()
{
  
  pinMode(2,INPUT); // Set to input so we can float it
  digitalWrite(2,LOW); // no pullup resistor = float this pin
  
  // start serial port at 115200 bps and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  //establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming string (don't care what it says)
    String ignored = Serial.readString();
    
    pinMode(2,OUTPUT); // switching pin 2 to output will show its state (LOW)
    delay(100);
    pinMode(2,INPUT); // switching pin 2 to input will return pin to float
    
    Serial.print("OK");
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("Press any key...");   // send an initial string
    delay(500);
  }
}
