
// the setup routine runs once when you press reset:
void setup() {                
  for (byte i=0; i<8; i++) {
    pinMode(2+i, OUTPUT);    
  } 
}

// the loop routine runs over and over again forever:
void loop() {

  for (int i=0; i<256; i++)
  {
    for (byte b=0; i<8; i++)
      digitalWrite(2+b, bitRead(i,b));
    
    delay(500);
  }
}
