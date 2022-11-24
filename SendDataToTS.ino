
#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;
// On Arduino:  0 - 1023 maps to 0 - 5 volts
#define VOLTAGE_MAX 5.0
#define VOLTAGE_MAXCOUNTS 1023.0

unsigned long myChannelNumber = 1945747;
const char * myWriteAPIKey = "HWT6K8KE33DZ3HQI";

void setup()
{
  Serial.begin(115200);
  Ethernet.begin(mac);
  ThingSpeak.begin(client);
}

void loop()
{
  // int sensorValue = analogRead(A0);
  int sensorValue = random(0,1023);
  float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  Serial.println(sensorValue);
  Serial.println(voltage);

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  delay(400000); // ThingSpeak will only accept updates every 5 minutes.
}

