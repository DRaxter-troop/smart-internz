Smart Parking System Prototype
This project implements a smart parking system for smart cities using IoT technology, as described in the provided document. It includes an Arduino-based hardware controller and a React web app for smartphones, communicating via a Node.js server with real HTTP requests.

Components
Arduino (smart_parking.ino): Runs on ESP8266 (NodeMCU) to manage:
RFID (MFRC522) for user authentication (entry/exit).
Two IR sensors for slot occupancy detection.
Servo motor for gate control.
Wi-Fi HTTP POST requests to update parking status.
React Web App (index.html): Mobile-friendly interface to display slot status, vehicle counts, and notifications, fetching data from the server.
Node.js Server (server.js): REST API to handle parking data, storing status in memory.

Hardware Setup
NodeMCU (ESP8266): Connect RFID (D3, D4, SPI), IR sensors (A0, D5), servo (D6).
Power: RFID/IR to 3.3V/5V, servo to 5V, GND shared.

Software Setup
Arduino:
Install libraries: MFRC522, Servo, ESP8266WiFi, ESP8266HTTPClient, ArduinoJson.
Update ssid, password, serverUrl in smart_parking.ino.
Upload to NodeMCU.
Server:
Install Node.js, npm.
Run npm init -y, npm install express in server directory.
Start: node server.js.
Use ngrok for public URL or deploy to Heroku/AWS.
React App:
Host index.html on a web server or open in a browser.
Update serverUrl to match server.

Usage
Entry: Scan RFID card; if slots available, gate opens, server updates.
Exit: Scan card again; gate opens, slot freed.
App: View slot status, vehicle counts, notifications. Use "Simulate Check-In/Out" for testing.
Server: Stores and serves parking data.
