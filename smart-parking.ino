#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Pin definitions for NodeMCU (ESP8266)
#define RST_PIN D3        // RFID RST pin
#define SS_PIN D4         // RFID SS pin
#define IR_SENSOR1 A0     // IR sensor for slot 1
#define IR_SENSOR2 D5     // IR sensor for slot 2
#define SERVO_PIN D6      // Servo motor pin

// Wi-Fi credentials
const char* ssid = "YourWiFiSSID"; // Replace with your Wi-Fi SSID
const char* password = "YourWiFiPassword"; // Replace with your Wi-Fi password
const char* serverUrl = "http://your-server-url/api/parking"; // Replace with your server URL

// Initialize components
MFRC522 rfid(SS_PIN, RST_PIN);
Servo gateServo;
WiFiClient wifiClient;
HTTPClient http;

// Simulated user database (RFID UID to username)
String users[2][2] = {
  {"1234", "Yeshes"},
  {"56789", "Abcd"}
};

// Parking slot status
bool slot1Occupied = false;
bool slot2Occupied = false;
int vehiclesEntered = 0;
int vehiclesExited = 0;
String parkedUsers[2] = {"", ""}; // Track users in slots

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  gateServo.attach(SERVO_PIN);
  gateServo.write(0); // Gate closed

  pinMode(IR_SENSOR1, INPUT);
  pinMode(IR_SENSOR2, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check IR sensors for slot status
  slot1Occupied = digitalRead(IR_SENSOR1) == LOW; // LOW means object detected
  slot2Occupied = digitalRead(IR_SENSOR2) == LOW;

  // Check for RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = getRFID_UID();
    String user = getUserByUID(uid);

    if (user != "") {
      // Check if user is already parked (for exit)
      int slotIndex = -1;
      for (int i = 0; i < 2; i++) {
        if (parkedUsers[i] == user) {
          slotIndex = i;
          break;
        }
      }

      if (slotIndex >= 0) {
        // User is exiting
        parkedUsers[slotIndex] = "";
        vehiclesExited++;
        sendHttpPost(user, false, slotIndex + 1, "Thanks for using smart parking, " + user + "!");
        gateServo.write(90);
        delay(2000);
        gateServo.write(0);
      } else if (!slot1Occupied || !slot2Occupied) {
        // User is entering
        int targetSlot = !slot1Occupied ? 1 : 2;
        parkedUsers[targetSlot - 1] = user;
        vehiclesEntered++;
        sendHttpPost(user, true, targetSlot, "Welcome, " + user + "! Slot " + String(targetSlot) + " allocated.");
        gateServo.write(90);
        delay(2000);
        gateServo.write(0);
      } else {
        sendHttpPost(user, false, 0, "No slots available!");
      }
    } else {
      Serial.println("Unauthorized card!");
    }
    rfid.PICC_HaltA();
  }

  // Update cloud with current status
  sendHttpPost("", false, 0, "");
  delay(5000); // Update every 5 seconds
}

String getRFID_UID() {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  return uid;
}

String getUserByUID(String uid) {
  for (int i = 0; i < 2; i++) {
    if (users[i][0] == uid) {
      return users[i][1];
    }
  }
  return "";
}

void sendHttpPost(String user, bool checkIn, int slot, String message) {
  if (WiFi.status() == WL_CONNECTED) {
    DynamicJsonDocument doc(512);
    doc["slot1"] = slot1Occupied;
    doc["slot2"] = slot2Occupied;
    doc["vehiclesEntered"] = vehiclesEntered;
    doc["vehiclesExited"] = vehiclesExited;
    if (user != "") {
      doc["user"] = user;
      doc["checkIn"] = checkIn;
      doc["slot"] = slot;
      doc["message"] = message;
    }

    String payload;
    serializeJson(doc, payload);

    http.begin(wifiClient, serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(payload);
    if (httpCode > 0) {
      Serial.println("HTTP POST successful: " + http.getString());
    } else {
      Serial.println("HTTP POST failed: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}