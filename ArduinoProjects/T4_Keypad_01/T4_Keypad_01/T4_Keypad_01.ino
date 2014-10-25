const bool debug=false;
const bool lcd=true;
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const byte r0 = A0;
const byte c0 = 2;
const char digits[][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
 
 // Rows are outputs, Cols are inputs
 for (byte r=0; r<4; r++) pinMode(r0+r,OUTPUT);
 for (byte c=0; c<4; c++) pinMode(c0+c,INPUT_PULLUP);
 
 Serial.begin(9600);
}

void loop(){
  byte pressed = ReadKeypad();
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}

char ReadKeypad()
{
  char pressed = '?';
  
  if (debug) Serial.println();
  for (byte r=0; r<4; r++)
  {
    if (debug) 
    {
      Serial.print("row ");
      Serial.print(r);
      Serial.print(": ");
    }
    digitalWrite(r0+r,LOW);
    
    for (byte c=0; c<4; c++) 
    {
      buttonState = digitalRead(c0+c);
      if (debug) {Serial.print(buttonState); Serial.print(" ");}
      if (buttonState==0)
      {
        pressed = digits[r][c];
        if (debug) {Serial.print("Pressed: "); Serial.println(pressed);}
        if (lcd) {
          Serial.write(0xFE);
          Serial.write(0x51);
          delay(5);
          Serial.print(pressed);
        }
      }
    }
    if (debug) Serial.println();
    digitalWrite(r0+r,HIGH);
  }
  
  return pressed;
}
