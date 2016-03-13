App:
Four areas:
- ipAddress
- Temperature
- power
- reboot

Arduino:
responds to:
gettemp
power
reboot


#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include "DHT.h"

#define USER_INFO       169
#define DEV_PORT        80
#define DEBUG_MSG

#define DHTPIN          2
#define DHTTYPE         DHT22

DHT dht(DHTPIN, DHTTYPE);

#define SHUTDOWN_PIN    6
#define RESTART_PIN     7

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP)
EthernetServer server(DEV_PORT);

bool userInfoFound = false;
bool userLoggedIn = false;
char user[32];
char pass[32];

char buf[128];
char* writePtr;

char arg1[32];
char arg2[32];
char arg3[32];

char *commands[5] = {"uszr-reg", "uszr-log", "comp-temp", "comp-pow", "comp-re"};

char *WRONG_LOGIN_MSG = "WRONG LOGIN";
char *NOT_REGISTERED_MSG = "NO USER REGISTERED";
char *REGISTERED_MSG = "USER REGISTERED";
char *ALREADY_REGISTERED_MSG = "USER ALREADY REGISTERED";

char *POWER_OFF_MSG = "SERVER POWERED OFF";
char *RESTART_MSG = "SERVER RESTARTED";

void getUserInfo(char* usr, char* pass)
{
  int addr = 1;

  while (EEPROM.read(addr) != 0)
  {
    *usr = EEPROM.read(addr);

    addr++;
    usr++;
  }

  *(usr - 1) = '\0';
  addr++;

  while (EEPROM.read(addr) != 0)
  {
    *pass = EEPROM.read(addr);

    pass++;
    addr++;
  }

  *(pass - 1) = '\0';
}

void setUserInfo(char* usr, char* pass)
{
  int addr = 1;

  while (*usr != '\0')
  {
    EEPROM.write(addr, *usr);

    addr++;
    usr++;
  }

  addr++;
  EEPROM.write(addr, *usr);
  addr++;

  while (*pass != '\0')
  {
    EEPROM.write(addr, *pass);

    addr++;
    pass++;
  }

  addr++;
  EEPROM.write(addr, *pass);
  EEPROM.write(0, USER_INFO);
}

void setup() {
  pinMode(SHUTDOWN_PIN, OUTPUT);
  pinMode(RESTART_PIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  if (EEPROM.read(0) != USER_INFO)
  {
    Serial.println(F("No user info found"));
    userInfoFound = false;
  }
  else
  {
    Serial.println(F("User info found"));
    userInfoFound = true;
    getUserInfo(user, pass);

#ifdef DEBUG_MSG
    Serial.print(F("USER: "));
    Serial.print(user);
    Serial.print(F("\tPASS: "));
    Serial.println(pass);
    Serial.println();
#endif

    digitalWrite(SHUTDOWN_PIN, LOW);
    digitalWrite(RESTART_PIN, LOW);
  }
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
#ifdef DEBUG_MSG
    Serial.println(F("New client"));
    Serial.println();
#endif

    while (client.connected())
    {
      if (client.available())
      {
        memset(buf, 0, sizeof(buf));
        writePtr = buf;

        char c;
        while ((c = client.read()) != '\n')
        {
          if (c >= 32)
          {
            *writePtr = c;
            writePtr++;
          }
        }
#ifdef DEBUG_MSG
        Serial.println();
#endif

#ifdef DEBUG_MSG
        Serial.println(F("Message Received"));
        Serial.println(buf);
        Serial.println();
#endif

        sscanf(buf, "%s %s %s", arg1, arg2, arg3);

        bool matchFound = false;
        for (byte i = 0; i < 5 && !matchFound; i++)
        {
          if (strcmp(arg1, commands[i]) == 0)
          {
            matchFound = true;
            switch (i)
            {
              case 0:
                if (!userInfoFound)
                {
                  setUserInfo(arg2, arg3);
                  userInfoFound = true;

                  client.println(REGISTERED_MSG);

#ifdef DEBUG_MSG
                  Serial.println(REGISTERED_MSG);
                  Serial.print(F("USER: "));
                  Serial.print(arg2);
                  Serial.print(F("\tPASS: "));
                  Serial.println(arg3);
                  Serial.println();
#endif
                }
                else
                {
                  client.println(ALREADY_REGISTERED_MSG);

#ifdef DEBUG_MSG
                  Serial.println(ALREADY_REGISTERED_MSG);
                  Serial.println();
#endif
                }
                break;

              case 2:
                if (userInfoFound)
                {
                  if (strcmp(arg2, user) == 0 && strcmp(arg3, pass) == 0)
                  {
                    client.println(dht.readTemperature(true));

#ifdef DEBUG_MSG
                    Serial.println(dht.readTemperature(true));
                    Serial.println();
#endif
                  }
                  else
                  {
                    client.println(WRONG_LOGIN_MSG);

#ifdef DEBUG_MSG
                    Serial.println(WRONG_LOGIN_MSG);
                    Serial.println();
#endif
                  }
                }
                else
                {
                  client.println(NOT_REGISTERED_MSG);

#ifdef DEBUG_MSG
                  Serial.println(NOT_REGISTERED_MSG);
                  Serial.println();
#endif
                }
                break;

              case 3:
                if (userInfoFound)
                {
                  if (strcmp(arg2, user) == 0 && strcmp(arg3, pass) == 0)
                  {
                    client.println(POWER_OFF_MSG);

#ifdef DEBUG_MSG
                    Serial.println(POWER_OFF_MSG);
                    Serial.println();
#endif

                    digitalWrite(SHUTDOWN_PIN, HIGH);
                    delay(1000);
                    digitalWrite(SHUTDOWN_PIN, LOW);
                  }
                  else
                  {
                    client.println(WRONG_LOGIN_MSG);

#ifdef DEBUG_MSG
                    Serial.println(WRONG_LOGIN_MSG);
                    Serial.println();
#endif
                  }
                }
                else
                {
                  client.println(NOT_REGISTERED_MSG);

#ifdef DEBUG_MSG
                  Serial.println(NOT_REGISTERED_MSG);
                  Serial.println();
#endif
                }
                break;

              case 4:
                if (userInfoFound)
                {
                  if (userInfoFound && strcmp(arg2, user) == 0 && strcmp(arg3, pass) == 0)
                  {
                    client.println(RESTART_MSG);

#ifdef DEBUG_MSG
                    Serial.println(RESTART_MSG);
                    Serial.println();
#endif

                    digitalWrite(RESTART_PIN, HIGH);
                    delay(1000);
                    digitalWrite(RESTART_PIN, LOW);

                  }
                  else
                  {
                    client.println(WRONG_LOGIN_MSG);

#ifdef DEBUG_MSG
                    Serial.println(WRONG_LOGIN_MSG);
                    Serial.println();
#endif
                  }
                }
                else
                {
                  client.println(NOT_REGISTERED_MSG);

#ifdef DEBUG_MSG
                  Serial.println(NOT_REGISTERED_MSG);
                  Serial.println();
#endif
                }
                break;

              default:
                matchFound = false;
                break;
            }
          }
        }

        if (!matchFound)
        {
          client.println("Command not valid");

#ifdef DEBUG_MSG
          Serial.println("Command not valid");
          Serial.println();
#endif
        }

        memset(buf, 0, sizeof(buf));
        writePtr = buf;

      }
    }

    delay(1);
    // close the connection:
    client.stop();
    userLoggedIn = false;

#ifdef DEBUG_MSG
    Serial.println("client disconnected");
    Serial.println();
#endif

    Ethernet.maintain();
  }
}

