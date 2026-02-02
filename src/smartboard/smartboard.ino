// Author: Suhel Mujawar
/*Note: In NodeMCU HIGH -> 0 and LOW -> 1*/

#include <ESP8266WiFi.h>
#include <Firebase.h>
#include "config.h"

// Relay configuration
// Defining pins
#define RELAY1 D1
#define RELAY2 D2

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


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
  if(Firebase.RTDB.getInt(&fbdo, "smartboard/devices/appliance1/state")){
    int state = fbdo.intData();
    if(state == 1){
      digitalWrite(RELAY1, LOW);
    }
    else{
      digitalWrite(RELAY1, LOW);  
    }

    else{
      Serial.println(fbdo.errorReason());
    }

    delay(350);// this avoid excessive firbase reads
  }
}

// Important Note :
/* Later i am going to upgrade to Firebase streaming from this
 traditional without streaming (polling) method.*/
