String ones[] = {"o'clock","one","two","three","four","five","six","seven","eight","nine"};
String tens[] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
String tys[] = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

String PrintWord(int num)
{
  String result = "";
  
  int onez = num % 10;
  int tenz = num / 10;
  
  if (tenz==0) 
  result = ones[onez];
  else if (tenz==1)
  result = tens[tenz-1];
  else result = tys[tenz-1] + " " + ones[onez];
}

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  establishContact();  // send a byte to establish contact until receiver responds

  for (int i=1; i<60; i++) {
    Serial.println( PrintWord(i) );
  }
}

void loop()
{
  int d2 = digitalRead(2);
  int d3 = digitalRead(3);
  int d4 = digitalRead(4);
  {
    Serial.print(d2);
    Serial.print(",");
    Serial.print(d3);
    Serial.print(",");
    Serial.println(d4);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}
