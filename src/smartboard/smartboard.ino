// Author: Suhel Mujawar
/*Note: In NodeMCU HIGH -> 0 and LOW -> 1*/
// Requires "Firebase ESP Client" by Mobizt
// Do NOT use older Firebase ESP32/ESP8266 libraries

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "config.h"
#include <time.h>

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
const char* appliancepath[4] = {
  "smartboard/devices/appliance1/state",
  "smartboard/devices/appliance2/state",
  "smartboard/devices/appliance3/state",
  "smartboard/devices/appliance4/state"
};
// Timer enable path
const char* timerpath[4] = {
  "smartboard/devices/appliance1/timer/enabled",
  "smartboard/devices/appliance2/timer/enabled",
  "smartboard/devices/appliance3/timer/enabled",
  "smartboard/devices/appliance4/timer/enabled"
};
// Timer start time path
const char* startpath[4] = {
  "smartboard/devices/appliance1/timer/start",
  "smartboard/devices/appliance2/timer/start",
  "smartboard/devices/appliance3/timer/start",
  "smartboard/devices/appliance4/timer/start"
};

// Timer duration path
const char* durationpath[4] = {
  "smartboard/devices/appliance1/timer/duration_min",
  "smartboard/devices/appliance2/timer/duration_min",
  "smartboard/devices/appliance3/timer/duration_min",
  "smartboard/devices/appliance4/timer/duration_min"
};

// corresponding pins 
const uint8_t pins[4] = {
  RELAY1,RELAY2,RELAY3,RELAY4
};

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800; 
const int daylightOffset_sec = 0;

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

   // Configure NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 4; i++){
  if(Firebase.RTDB.getBool(&fbdo, appliancepath[i])){
    bool state = fbdo.boolData();
    if(state){
      digitalWrite(pins[i], LOW);
    }
    else{
      digitalWrite(pins[i], HIGH);  
    }
    if(Firebase.RTDB.getBool(&fbdo, timerpath[i])){
      bool enabled = fbdo.boolData();
      if(enabled){
        // Calculate current time 
          struct tm timeinfo;

          if (!getLocalTime(&timeinfo)) {
              Serial.println("Failed to obtain time");
              delay(1000);
              return;
            }


          char timeStr[6];
          sprintf(timeStr, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
          Serial.println(timeStr);
          // Fetch timer value
          if(Firebase.RTDB.getString(&fbdo, startpath[i])){
            String startTime = fbdo.stringData();
            if(Firebase.RTDB.getInt(&fbdo, durationpath[i])){
                int durationMin = fbdo.intData();
                int currentMin = timeinfo.tm_hour * 60 + timeinfo.tm_min;

                int startHour = startTime.substring(0,2).toInt();
                int startMin = startTime.substring(3,5).toInt();
                int startTotalMin = startHour * 60 + startMin;

                if(currentMin >= startTotalMin + durationMin){
                    digitalWrite(pins[i], HIGH);
                    Firebase.RTDB.setInt(&fbdo, appliancepath[i], 0);
                }
          } 

            if(String(timeStr) == startTime){
              digitalWrite(pins[i], LOW);
              Firebase.RTDB.setInt(&fbdo, appliancepath[i] , 1);
            }
          }else{
            Serial.println(fbdo.errorReason());
          }
      }
    }
  }
    else{
      Serial.println(fbdo.errorReason());
    }
  }
    delay(2000);// this avoid excessive firbase reads
}

// Important Note :
/* Later i am going to upgrade to Firebase streaming from this
 traditional without streaming (polling) method.*/
