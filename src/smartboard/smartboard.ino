// Author: Suhel Mujawar

#include <ESP8266WiFi.h>
#include "config.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  Serial.println();
  Serial.println("Connecting to WiFi");

  // Establish WiFi connection
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
}
