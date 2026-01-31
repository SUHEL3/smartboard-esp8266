# SmartBoard ESP8266 🔌📱

A cloud-connected **Smart Extension Board** built using **ESP8266 (NodeMCU)** and **Firebase Realtime Database**, controlled via an Android application.

## Features
- Control multiple electrical sockets remotely
- Real-time sync using Firebase RTDB
- Secure authentication
- Works from anywhere (no local network dependency)
- Scalable to N relays

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
	  "appliance1": false,
	  "appliance2": false,
	  "appliance3": false,
          "appliance4": false
	}
  }
}
