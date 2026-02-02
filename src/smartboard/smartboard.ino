// Author: Suhel Mujawar
/*Note: In NodeMCU HIGH -> 0 and LOW -> 1*/

#include <ESP8266WiFi.h>
#include "config.h"

// Relay configuration
// Defining pins
#define RELAY1 D1
#define RELAY2 D2

void setup() {
  // put your setup code here, to run once:
  // Configuring relay pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  
  // Keeping relay OFF at startup
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);

  Serial.begin(115200);

  Serial.println();
  Serial.println("Connecting to WiFi");

  // Establish WiFi connection(tested)
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

   // Establishing WiFi connection
   while(WiFi.status() != WL_CONNECTED){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(".");
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
   }

  // WiFi connected successfully
  Serial.println();
  Serial.println("WiFi connected successfully.");
  Serial.print("WiFi IP:");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  // For testing relays :
  Serial.println("Relay1 ON.")
  digitalWrite(RELAY1, LOW);
  delay(1000);
  digitalWrite(RELAY1, HIGH);
  Serial.println("Relay2 ON.")
  digitalWrite(RELAY2, LOW);
  delay(1000);
  digitalWrite(RELAY2, HIGH);
}
