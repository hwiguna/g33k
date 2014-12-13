// ESP8266 + Arduino Demo - by Hari Wiguna, 2014
//
// There are two pieces of this app:
// 1. ESP8266 side: Creates a WebServer to listen for anything.  Upon receiving web request from a browser, it prints it for the Arduino to consume
// 2. Arduino side: Listens on Serial (D0, D1) for led0 or led1 to control an LED.

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int ledPin = 2;

void setup() {
  // initialize serial:
  //Serial.begin(9600); // debug
  Serial.begin(9600);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString);  
    //Serial1.println(inputString);  // Don't send anything TO Serial1 because lua is expecting lua statements! send debugs to other serial port.
    ProcessInput(inputString);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void ProcessInput(String inputString)
{
  String command = inputString.substring(0,3); // first parameter is BEFORE the desired char. second parameter is THE last desired char
  String param = inputString.substring(3,4);
  //Serial1.print("inputString="); Serial1.println(inputString);
  //Serial1.print("command="); Serial1.println(command);
  //Serial1.print("param="); Serial1.println(param);
  if (command == "led") {
    digitalWrite(ledPin, param=="1");
  }
}

