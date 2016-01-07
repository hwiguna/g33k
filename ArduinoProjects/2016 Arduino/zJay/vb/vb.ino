int ledR= 8; 
int ledG= 9; 
int ledB= 10; 

void setup()
{
   pinMode(ledR,OUTPUT); 
   pinMode(ledG,OUTPUT); 
   pinMode(ledB,OUTPUT);
   
   Serial.begin(9600); 
}

void loop()
{
  int val, r, g, b;
  
  if (Serial.available())
  {
    delay(100);  
    while  (Serial.available ()>9) 
    {
      val=Serial.read();
      int number[8] = {0,0,0,0,0,0,0,0}; 
      
    for (int i = 0; i < 9; i = i++)   
    {
      number[i]= Serial.read();
    }
    
    int num0 = number[0]-'0';   
    int num1 = number[1]-'0';
    int num2 = number[2]-'0'; 
    r= num0*100+ num1*10 + num2;
    
    int num3=  number[3]-'0';     
    int num4 = number[4]-'0';
    int num5 = number[5]-'0'; 
    g= num3*100+ num4*10 + num5;
    
    int num6 = number[6]-'0';    
    int num7=  number[7]-'0'; 
    int num8=  number[8]-'0';   
    b= num6*100+ num7*10 + num8;
    
    color( r, g, b); 
      
    }
    Serial.flush();
  }
}   

 void color(int red, int green, int blue)
{
    analogWrite(ledR, red);
 
    analogWrite(ledG, green);
 
    analogWrite(ledB, blue);
}


