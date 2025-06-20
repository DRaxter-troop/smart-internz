#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define IR1_PIN D1
#define IR2_PIN D2
#define IR3_PIN D3
#define OUT_DOOR_SERVO_PIN D4
#define IN_DOOR_SERVO_PIN D5

const char* ssid = "Test";
const char* password = "password123";
const char* serverName = "http://localhost:3000";

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo outDoorServo;
Servo inDoorServo;

bool slots[3] = {false, false, false};

void setup() {
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);
  outDoorServo.attach(OUT_DOOR_SERVO_PIN);
  inDoorServo.attach(IN_DOOR_SERVO_PIN);
  outDoorServo.write(0);
  inDoorServo.write(0);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  slots[0] = !digitalRead(IR1_PIN);
  slots[1] = !digitalRead(IR2_PIN);
  slots[2] = !digitalRead(IR3_PIN);

  lcd.setCursor(0, 1);
  lcd.print("S1:");
  lcd.print(slots[0] ? "X" : "O");
  lcd.print(" S2:");
  lcd.print(slots[1] ? "X" : "O");
  lcd.print(" S3:");
  lcd.print(slots[2] ? "X" : "O");

  if (slots[0] && slots[1] && slots[2]) {
    outDoorServo.write(0);
    inDoorServo.write(0);
    sendToWebServer("All slots occupied");
  } else {
    outDoorServo.write(90);
    inDoorServo.write(90);
    String message = "Free slots: ";
    if (!slots[0]) message += "1 ";
    if (!slots[1]) message += "2 ";
    if (!slots[2]) message += "3";
    sendToWebServer(message);
    delay(5000);
    outDoorServo.write(0);
    inDoorServo.write(0);
  }

  delay(100);
}

void sendToWebServer(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"status\":\"" + message + "\", \"slot1\":" + String(slots[0]) + ", \"slot2\":" + String(slots[1]) + ", \"slot3\":" + String(slots[2]) + "}";
    http.POST(jsonData);
    http.end();
  }
}