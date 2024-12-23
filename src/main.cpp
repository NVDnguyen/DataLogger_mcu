#include <Arduino.h>
#include "aws_iot.h"
#include "my_wifi.h"
#include "utils.h"
unsigned long lastMillis = 0;
AWSIoT awsIoT;
MYWIFI myWIFI;

void setup()
{
  Serial.begin(115200);
  myWIFI.connect();
  awsIoT.begin();
}

void loop()
{
  // Check if data is available to read
  if (Serial.available() > 0)
  {
    String str = Serial.readStringUntil('\n');
    Serial.print("\n> Recieve: ");
    Serial.println(str);

    // Allocate buffer for JSON
    char *json = (char *)malloc(200);
    if (json == nullptr)
    {
      Serial.println("> Memory allocation failed");
    }
    else
    {
      // Convert to JSON
      if (convertDataToJson(str, json,200) == SUCCESS)
      {
        // Publish to AWS IoT
        awsIoT.publishMessage(json);
        Serial.print("> AWS Sent: ");
        Serial.println(json);
      }else{
        Serial.print("> ERROR: ");
        Serial.println("Cannot convert string to json");
      }

      free(json);
    }
  }

  awsIoT.loop();
}
