// Vers 3 - Actually start on T4 functionality

#include <SoftwareSerial.h>

SoftwareSerial softSerial(10, 11); // RX, TX

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

char hitLastChar = '?'; // What was the last key hit?
byte hitCount = 0; // How many times has the same key been hit?
unsigned long hitLastTime = 0; // When was the last time that same key was hit?
enum States {
  idle,
  keyHit,
  keyWait,
  keyAccept
};
States state = idle;

int charPos = 0; // How many chars are on screen so far?

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
 
 // Rows are outputs, Cols are inputs
 for (byte r=0; r<4; r++) pinMode(r0+r,OUTPUT);
 for (byte c=0; c<4; c++) pinMode(c0+c,INPUT_PULLUP);
 
 Serial.begin(9600);
 softSerial.begin(9600);

 writeCommand(0x51); // Clear Screen
}

void writeCommand(byte cmd)
{
  softSerial.write(0xFE);
  softSerial.write(cmd);
}

void writeCommand(byte cmd, byte param1)
{
  softSerial.write(0xFE);
  softSerial.write(cmd);
  softSerial.write(param1);
}

void loop(){
//  softSerial.print("Hello");
//  delay(1000);
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
  
  for (byte r=0; r<4; r++) 
  {
    digitalWrite(r0+r,LOW);
    
    for (byte c=0; c<4; c++) 
    {
      buttonState = digitalRead(c0+c);
      if (buttonState==0)
      {
        pressed = digits[r][c];
        writeCommand(0x45, charPos);// Set Cursor
        delay(10);
        
        if (pressed == hitLastChar) state=keyHit;
        switch (state)
        {
          case idle: break;
          case keyHit: 
            hitCount = (hitCount + 1) % 4;
            state = keyWait;
            
            break;
          case keyWait: 
            
            break;
          case keyAccept: break;
        }
        
        else hitCount=1;
        if (hitCount>4) hitCount=1;
        hitLastChar = pressed;
        
          char toDisplay = pressed;
          switch (hitCount)
          {
            case 1: toDisplay='2'; break;
            case 2: toDisplay='A'; break;
            case 3: toDisplay='B'; break;
            case 4: toDisplay='C'; break;
          }
        softSerial.print(toDisplay);

        //if (hitCount==1) charPos++;
        //hitLastTime = millis();
        delay(500);
      }
    }
    digitalWrite(r0+r,HIGH);
  }
  
  return pressed;
}
