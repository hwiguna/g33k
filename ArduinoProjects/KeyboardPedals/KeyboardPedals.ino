const byte firstPedalPin = 2;
const byte pedalCount = 4;

void setup () {
  for (byte i=0; i<pedalCount; i++)
    pinMode(pedalOne, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()  {
  for (byte i=0; i<pedalCount; i++)
  
  {
    bool isPressed = (digitalRead(firstPedalPin+i) == LOW);
    String state = isPressed ? " pressed" : " off";
    Serial.print("p");
    Serial.print(i+1);
    Serial.println(state);
  }
  Serial.println(); // Space between each group of pedal states
}


