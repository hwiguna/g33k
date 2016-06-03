float startChargingAt = 10.20; // volts  //set the voltage considered low battery here
float STOPChargingAt = 12.5; // volts  //set the voltage considered FULL battery here

#define transistor_pin 13

void setup()
{
  pinMode(transistor_pin, OUTPUT);
  digitalWrite(transistor_pin, LOW);
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (12.20 / 1023.00) * 2; //convert the value to a true voltage.
  Serial.print("voltage = ");
  Serial.print(voltage); //print the voltage to Serial
  Serial.print(" V ");

  if (voltage <= startChargingAt )
  {
    Serial.print("Charging Started...");
    digitalWrite(transistor_pin, HIGH);
  }

  if (voltage >= STOPChargingAt )
  {
    Serial.print("Charging STOPPED");
    digitalWrite(transistor_pin, LOW);
  }
  Serial.println();

  delay(1000); // This probably could be even higher
}
