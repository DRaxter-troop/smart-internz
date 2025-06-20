Install Arduino IDE: Download the Arduino IDE from arduino.cc for your OS (Windows, Mac, or Linux). Install it by following the prompts—easy as pie!
Add ESP8266 Support: Open Arduino IDE, go to File > Preferences, and add http://arduino.esp8266.com/stable/package_esp8266com_index.json to “Additional Boards Manager URLs.” 
Click “OK,” then go to Tools > Board > Boards Manager, search “esp8266,” and install the package. 
Connect ESP8266: Plug your ESP8266 into your laptop via USB. In Arduino IDE, select Tools > Board > NodeMCU 1.0 (ESP-12E Module) and pick the port (e.g., COM3 or /dev/ttyUSB0) under Tools > Port.
Prepare Code: Copy the provided code into a new sketch (File > New), save it as “smart_parking_esp8266_phone.ino.” Update serverName to your laptop’s IP (e.g., "WTF IP via ipconfig or ifconfig).
Install Libraries: Go to `Sketch > Include Library > Manage Libraries,” and install “ESP8266WiFi,” “ESP8266HTTPClient,” “LiquidCrystal_I2C” by Frank de Brabander, and “Servo.”
Wire Hardware: Connect IR sensors to D1, D2, D3; Out Door Servo to D4, In Door Servo to D5; and LCD with a +5V/+12V power supply. Double-check connections—safety first!
Upload Code: Click the Upload button (or Ctrl+U) in Arduino IDE to send the code to the ESP8266. Watch the output window—if it says “Done uploading,” you’re set!

Set Up Web Server for Phone: Install Node.js

Run it with node server.js in your terminal.
Test on Laptop: Open Serial Monitor (Tools > Serial Monitor, 115200 baud). Wave hands over IR sensors—LCD should show “X” (occupied) or “O” (free), and servos should open/close.
Test on Phone: On your phone (same “Test” Wi-Fi), open a browser and go to http://192.168.1.100:3000 (use your laptop’s IP). The server will log data. For a UI, host a simple HTML page on the server to display it.
