int c0 = 6; // Starting column pin
int r0 = 2; // Starting row pin

void setup() {
  //Keyboard.begin();
  Serial.begin(9600);

  //-- Setup columns as outputs --
  for (byte c = 0; c < 10; c++)
  {
    pinMode(c0 + c, OUTPUT);
    digitalWrite(c0 + c, LOW); // Set all columns to LOW
  }

  //-- Setup rows as inputs --
  for (byte r = 0; r < 4; r++)
  {
    pinMode(r0 + r, INPUT);
    digitalWrite(r0 + r, HIGH); // Enable built-in pullup resistor
  }
}

void loop() {
  for (byte c = 0; c < 10; c++)
  {
    digitalWrite(c0 + c, LOW); // Put 5V in one of the columns
    for (byte r = 0; r < 4; r++)
    {
      if (digitalRead(r0 + r)==0)
      {
        Serial.print(r);
        Serial.print(",");
        Serial.print(c);

        if (r == 0 && c == 9) {
          //Keyboard.press(KEY_ESC);
          Serial.print(" A1");
        }

        if (r == 0 && c==8) {
          //Keyboard.press(KEY_LEFT_CTRL); // Control
          //Keyboard.press('n');          // and n
          Serial.print(" A0");
        }

        //:::::::::::::::::::::::::::::::::::::::::::
        //... Keep adding more IF statements here ...
        //:::::::::::::::::::::::::::::::::::::::::::
        

        // No matter what key was pressed, release it.
        while (digitalRead(r0+r)==0) delay(10);
        //Keyboard.releaseAll();
         
        Serial.println();
      }
    }
    digitalWrite(c0 + c, HIGH); // Turn off that column to get ready for the next column
  }
}
