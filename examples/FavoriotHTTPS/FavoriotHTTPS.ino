/*
* Author: Mohamad Ariffin Zulkifli
* Organization: Myinvent Technologies Sdn Bhd
*
* This sketch has 3 execution steps:
* 1. Initialized Favoriot connectivity
* 2. Sensors reading for data acquisition
* 3. Send data to Favoriot Data Stream
* 
* Please select ESP8266 Boards before compiling the sketch
* (example) Go to menu, Tools > Board > NodeMCU 1.0 (ESP-12E Module)
*
*/

#include <Favoriot.h>

String ssid     = "YourWiFiSSID";           // replace with your WiFi SSID
String password = "YourWiFiPassword";       // replace with your WiFi password
String apikey   = "YourDeviceAccessToken";  // replace with your Favoriot Device Access Token

FavoriotHTTPS favoriot;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  // STEP 1 - Initialized Favoriot connectivity
  favoriot.begin(ssid, password, apikey);
}

void loop() {
  
  // STEP 2 - Sensors reading for data acquisition
  byte suhu = random(22, 26);
  byte kelembapan = random(45, 55);

  // update data interval to Favoriot Data Stream using millis function
  if(millis() - previousMillis > 10000){
    previousMillis = millis();

    // STEP 3 - Send data to Favoriot Data Stream
    favoriot.deviceId("YourDeviceDeveloperId");
    favoriot.dataStream("suhu", String(suhu));
    favoriot.dataStream("kelembapan", String(kelembapan));
    favoriot.dataStreamEnd();

  }
}
