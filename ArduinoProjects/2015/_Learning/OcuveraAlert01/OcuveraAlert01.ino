
int inByte = 0;         // incoming serial byte

void setup()
{
  
  pinMode(2,INPUT); // Set to input so we can float it
  digitalWrite(2,LOW); // no pullup resistor = float this pin
  
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    Serial.print("Sending!");
    
    pinMode(2,OUTPUT); // switching pin 2 to output will show its state (LOW)
    delay(100);
    pinMode(2,INPUT); // switching pin 2 to input will return pin to float
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("Press any key...");   // send an initial string
    delay(1000);
  }
}
