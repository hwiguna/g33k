   //////////////////////////////////////////////
  //        Arduino Voltmeter Project         //
 //            with NOKIA 5110 LCD           //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////


#include <LCD5110_Graph.h> // THE LIBRARY I AM USING IS THIS:  http://www.rinkydinkelectronics.com/library.php?id=47


LCD5110 lcd(13,11,8,10,9);
//LCD5110(int SCK, int MOSI, int DC, int RST, int CS);

extern unsigned char BigNumbers[];
extern uint8_t ui[];
extern uint8_t startScreen[];

float voltage = 0.0;
int sensorPin = A5;  
float sensorValue = 0.0f;  
String voltageString ="0.0";
int stringLength = 0;

float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; 
float R2 = 7500.0; 
 
void setup() {
  Serial.begin(9600);
  lcd.InitLCD();
  lcd.drawBitmap(0, 0, startScreen, 84, 48);
  lcd.update();
  delay(3000);
  lcd.setFont(BigNumbers);
  lcd.setContrast(60);
  delay(1000);
}

void loop() {
  lcd.clrScr();
  lcd.drawBitmap(0, 0, ui, 84, 48);

  voltage = readVoltage();
    
  Serial.println(voltage);

  voltageString = String(voltage,1);
 
  stringLength = voltageString.length();
  displayVoltage(stringLength);
  lcd.update();
  delay(1000);
}


float readVoltage()
{

   sensorValue = analogRead(sensorPin);
   vout = (sensorValue * 5.0) / 1024.0; 
   vin = vout; // / (R2/(R1+R2)); 
   return vin;
}

void displayVoltage(int length)
{
  switch(length)
  {
    case 3:  lcd.print(voltageString,14,19); break;
    case 4:  lcd.print(voltageString,2,19); break;
    default:  lcd.print(voltageString,2,19); break;
  }
}

