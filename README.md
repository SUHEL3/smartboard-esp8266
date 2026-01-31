# SmartBoard ESP8266 

A cloud-connected **Smart Extension Board** built using **ESP8266 (NodeMCU)** and **Firebase Realtime Database**, controlled via an Android application.

## Features
- Control multiple electrical sockets remotely
- Real-time sync using Firebase RTDB
- Secure authentication
- Works from anywhere (no local network dependency)
- Scalable to N relays

### Timer-Based Automation
Users can schedule appliances to turn ON at a specific time
and automatically turn OFF after a defined duration using
cloud-based scheduling with Firebase RTDB and NTP time sync.

## Architecture
Android App → Firebase RTDB → ESP8266 → Relay Module(connected to extension board switches) → Appliances

## Tech Stack
- ESP8266 (NodeMCU)
- Firebase Realtime Database
- Arduino IDE
- Android (Firebase SDK)
- Wi-Fi Networking

## project Structure
  src/
├── smartboard.ino
└── config.h (ignored)



## Setup Instruction

1. Clone the repository
2. Create `config.h` inside `src/`
3. Add your Wi-Fi and Firebase credentials
4. Upload code to ESP8266
5. Control relays using Firebase

## Firebase Data Structure
```json
{
  "smartboard": {
     "devices":{
	  "appliance1": {
      "state": 0,
      "timer": {
        "enabled": true,
        "start": "18:30",
        "duration_min": 30
      },
	  "appliance2": {
      "state": 0,
      "timer": {
        "enabled": true,
        "start": "18:30",
        "duration_min": 30
      },
	  "appliance3": {
      "state": 0,
      "timer": {
        "enabled": true,
        "start": "18:30",
        "duration_min": 30
      },
 	  "appliance4": {
      "state": 0,
      "timer": {
        "enabled": true,
        "start": "18:30",
        "duration_min": 30
      }
	}
  }
}

## Safety Disclaimer
This project involves using ralay module with AC loads 
,hence user must ensure proper electrical isolation and
safety measures.
