void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  establishContact();  // send a byte to establish contact until receiver responds 
  
  //Test();
}

void loop()
{
  AnalogDump();
}

void AnalogDump()
{
  int a = analogRead(A5);
  Serial.print(a);
  if (a>200) Serial.print(" ***");
  Serial.println();
  delay(100);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}

void Test()
{
  Serial.println("Hello");
  
  float lastY = 0;
  for (float time=0; time < 4.83; time = time+0.032) // Increment = granularity
  {
    float freq = 1; //oscillations per second 
    float amplitude =  7; 
    float decay =  0.3; // Smaller = Slower decay = lasts longer
    
    float posCos = abs(cos(freq*time*2*PI));
    float y = floor( amplitude*posCos/exp(decay*time) );
    
    Serial.print(time);
    Serial.print(" -> ");
    Serial.print(y);
    Serial.print(" | ");
    Serial.print(y);
    
    if (y != lastY) {
      lastY = y;
      Serial.print(" *");
    }
    
    Serial.println();
  }
}


