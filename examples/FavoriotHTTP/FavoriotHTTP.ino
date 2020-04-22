/*
* Author: Mohamad Ariffin Zulkifli
* Organization: Myinvent Technologies Sdn Bhd
*
* This sketch has 3 execution steps:
* 1. Initialized Favoriot connectivity
* 2. Sensors reading for data acquisition
* 3. Send data to Favoriot Data Stream
*
* Please select ESP32/ESP8266 Boards before compiling the sketch
* (example) Go to menu, Tools > Board > ESP32 Arduino or ESP8266 Boards
* 
*/

#include <Favoriot.h>

char ssid[]     = "YourWiFiSSID";           // replace with your WiFi SSID
char password[] = "YourWiFiPassword";       // replace with your WiFi password
char apikey[]   = "YourDeviceAccessToken";  // replace with your Favoriot Device Access Token

FavoriotHTTP favoriot;

void setup() {
  Serial.begin(9600);

  // STEP 1 - Initialized Favoriot connectivity
  favoriot.begin(ssid, password, apikey);
}

void loop() {
  
  // STEP 2 - Sensors reading for data acquisition
  byte suhu = random(22, 26);
  byte kelembapan = random(45, 55);

  // STEP 3 - Send data to Favoriot Data Stream
  favoriot.deviceId("YourDeviceDeveloperId");
  favoriot.dataStream("suhu", String(suhu));
  favoriot.dataStream("kelembapan", String(kelembapan));
  favoriot.dataStreamEnd();
  
  delay(10000); // update data interval to Favoriot Data Stream using delay function
  
}
