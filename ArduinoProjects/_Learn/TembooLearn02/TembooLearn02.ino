#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;
// The number of times to trigger the action if the condition is met.
// We limit this so you won't use all of your Temboo calls while testing.
int maxCalls = 2;

// The number of times this Choreo has been run so far in this sketch.
int calls = 0;

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected.
  delay(4000);
  while(!Serial);

  Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while(true);
  }
  Serial.println("OK");
  delay(5000);
  // Initialize pins
  pinMode(A2, INPUT);
  pinMode(13, OUTPUT);
  
  Serial.println("Setup complete.\n");
}

void loop() {
  int sensorValue = analogRead(A2);
  
  Serial.println("Sensor: " + String(sensorValue));
  
  if (sensorValue<100) {
    if (calls < maxCalls) {
      Serial.println("\nTriggered! Calling /Library/Google/Gmail/SendEmail...");
  
      runSendEmail(sensorValue);
      digitalWrite(13, HIGH);
      calls++;
    } else {
      Serial.println("\nTriggered! Skipping the action to save Temboo calls during testing.");
      Serial.println("You can adjust or remove the calls/maxCalls if() statement to change this behavior.\n");
    }
  }
  delay(250);
}

void runSendEmail(int sensorValue) {
  TembooChoreo SendEmailChoreo(client);

  // Set Temboo account credentials
  SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
  SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set saved inputs to use for execution
  SendEmailChoreo.setSavedInputs("arduinoGenericEmail");

  // Set Choreo inputs
  String MessageBodyValue = String("The current sensor value is: ") + String(sensorValue);
  SendEmailChoreo.addInput("MessageBody", MessageBodyValue);

  // Identify the Choreo to run
  SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");

  // Run the Choreo
  unsigned int returnCode = SendEmailChoreo.run();

  // A return code of zero means everything worked
  if (returnCode == 0) {
    Serial.println("Done!\n");
  } else {
    // A non-zero return code means there was an error
    // Read and print the error message
    while (SendEmailChoreo.available()) {
      char c = SendEmailChoreo.read();
      Serial.print(c);
    }
    Serial.println();
  }
  
  SendEmailChoreo.close();
}
