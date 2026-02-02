// Author: Suhel Mujawar
/*Note: In NodeMCU HIGH -> 0 and LOW -> 1*/
// Requires "Firebase ESP Client" by Mobizt
// Do NOT use older Firebase ESP32/ESP8266 libraries

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "config.h"

// Relay configuration
// Defining pins
#define RELAY1 D1
#define RELAY2 D2
#define RELAY3 D3
#define RELAY4 D4

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Firebase RTDB paths array
const char* path[4] = {
  "smartboard/devices/appliance1/state",
  "smartboard/devices/appliance2/state",
  "smartboard/devices/appliance3/state",
  "smartboard/devices/appliance4/state"
};
// corresponding pins 
const uint8_t pins[4] = {
  RELAY1,RELAY2,RELAY3,RELAY4
};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Configuring relay pins and keeping relay OFF at startup
  for(int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }

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

  // Firebase code
  Serial.println("Connecting Firebase.");
  // database configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  //authentication configuration
  auth.user.email = FIREBASE_EMAIL;
  auth.user.password = FIREBASE_PASSWORD;

  // Connecting firebase
  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);
  Serial.println("Firebase connected.");
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 4; i++){
  if(Firebase.RTDB.getInt(&fbdo, path[i])){
    int state = fbdo.intData();
    if(state == 1){
      digitalWrite(pins[i], LOW);
    }
    else{
      digitalWrite(pins[i], HIGH);  
    }
  }
    else{
      Serial.println(fbdo.errorReason());
    }
  }
    delay(350);// this avoid excessive firbase reads
}

// Important Note :
/* Later i am going to upgrade to Firebase streaming from this
 traditional without streaming (polling) method.*/
