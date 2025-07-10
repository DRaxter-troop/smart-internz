Smart Parking System Prototype
This project implements a smart parking system for smart cities using IoT technology, as described in the provided document. It includes an ESP32DEVKIT1 hardware controller and a Blynk app for smartphones, communicating via a wifi server with real requests.

Components

Uses ESP32DEVKITV1 as master and wifi module
Three IR sensors for slot occupancy detection
Wi-Fi HTTP POST requests to update parking status.

Hardware Setup
3IR sensors are connected to ESP32 (D35,D33,D27)

Software Setup
Arduino:
Install libraries: , ESP8266WiFi, ESP8266HTTPClient, Arduino Blynksetup.
Update ssid, password, serverUrl in smart_parking.ino.
Upload to NodeMCU.
Input project ID, authentication token given on Blynk
Server


