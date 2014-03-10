const int xSensor = A5;  // Analog input pin that the potentiometer is attached to
const int ySensor= A4;  // Analog input pin that the potentiometer is attached to
const int zSensor = A3;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
    int xValue = analogRead(xSensor);
    int yValue = analogRead(ySensor);
    int zValue = analogRead(zSensor);
    
    Serial.print(xValue); Serial.print(", "); 
    Serial.print(yValue); Serial.print(", "); 
    Serial.print(zValue); Serial.println(); 

  outputValue = map(sensorValue, 0, 1023, 0, 255);  

  // print the results to the serial monitor:
//  Serial.print("sensor = " );                       
//  Serial.print(sensorValue);      
//  Serial.print("\t output = ");      
//  Serial.println(outputValue);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);                     
}
