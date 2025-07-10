// Blynk 2.0 configuration
#define BLYNK_TEMPLATE_ID "TMPL3-YM2alBw"
#define BLYNK_TEMPLATE_NAME 
#define BLYNK_AUTH_TOKEN "_y_f6FQYr"Smart Parking system"iN_rXukvC1-LKiuAemlPaiR"  // Replace with your Blynk Auth Token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "Jadhav_2.4GHz";  // 
char pass[] = "********";  // 

// Pin definitions for IR sensors
#define IR_SENSOR_1 26  // D26
#define IR_SENSOR_2 25  // D25
#define IR_SENSOR_3 33  // D33

// Variables to store parking slot status
bool slot1_status = false;
bool slot2_status = false;
bool slot3_status = false;

void setup() {
  
  Serial.begin(115200);
  delay(1000); 
  
  
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  pinMode(IR_SENSOR_3, INPUT);
  
  
  Serial.println("Testing IR Sensors at Startup...");
  Serial.print("IR Sensor 1 (Pin D26): ");
  Serial.println(digitalRead(IR_SENSOR_1) ? "Active (HIGH)" : "Active (LOW)");
  Serial.print("IR Sensor 2 (Pin D25): ");
  Serial.println(digitalRead(IR_SENSOR_2) ? "Active (HIGH)" : "Active (LOW)");
  Serial.print("IR Sensor 3 (Pin D33): ");
  Serial.println(digitalRead(IR_SENSOR_3) ? "Active (HIGH)" : "Active (LOW)");
  
  
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
int wifi_timeout = 10; 
  while (WiFi.status() != WL_CONNECTED && wifi_timeout > 0) {
    delay(1000);
    Serial.print(".");
    wifi_timeout--;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Check SSID/password or signal strength.");
  }
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop
  if (Blynk.connected()) {
    Serial.println("Blynk is connected!");
    Blynk.run(); 
  } else {
    Serial.println("Blynk is disconnected. Attempting to reconnect...");
    Blynk.connect(); /
  }
  slot1_status = digitalRead(IR_SENSOR_1);
  slot2_status = digitalRead(IR_SENSOR_2);
  slot3_status = digitalRead(IR_SENSOR_3);
  Blynk.virtualWrite(V1, !slot1_status); 
  Blynk.virtualWrite(V2, !slot2_status);
  Blynk.virtualWrite(V3, !slot3_status); 
  Serial.println("\nIR Sensor Status:");
  Serial.print("Sensor 1 (D26): ");
  Serial.print(slot1_status ? "HIGH (Car Detected)" : "LOW (No Car)");
  Serial.println(slot1_status ? " -> Slot 1: Occupied (Red)" : " -> Slot 1: Available (Green)");
  Serial.print("Sensor 2 (D25): ");
  Serial.print(slot2_status ? "HIGH (Car Detected)" : "LOW (No Car)");
  Serial.println(slot2_status ? " -> Slot 2: Occupied (Red)" : " -> Slot 2: Available (Green)");
  Serial.print("Sensor 3 (D33): ");
  Serial.print(slot3_status ? "HIGH (Car Detected)" : "LOW (No Car)");
  Serial.println(slot3_status ? " -> Slot 3: Occupied (Red)" : " -> Slot 3: Available (Green)");
  
  /
  delay(1000);
}


