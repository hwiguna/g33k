
int oldD2, oldD3, oldD4;

void setup()
{
  SREG = SREG | _BV(SREG_I); // Enable global interrupt

  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  int d2 = digitalRead(2);
  int d3 = digitalRead(3);
  int d4 = digitalRead(4);
  if (d2 != oldD2 || d3 != oldD3 || d4 != oldD4)
  {
    Serial.print(d2);
    Serial.print(",");
    Serial.print(d3);
    Serial.print(",");
    Serial.println(d4);
    oldD2 = d2;
    oldD3 = d3;
    oldD4 = d4;
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}
