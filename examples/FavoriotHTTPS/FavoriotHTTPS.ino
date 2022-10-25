/*
* Author: Mohamad Ariffin Zulkifli
* Organization: Myinvent Technologies Sdn Bhd
*
* This sketch has 3 execution steps:
* 1. Initialized Wi-Fi and IoT platform conectivity (Favoriot)
* 2. Data Acquisition - Read data from the sensors
* 3. Data Ingestion - Send data to Favoriot's data stream
*
* Please select ESP8266/ESP32 Boards before compiling the sketch
* (example) Go to menu, Tools > Board > ESP8266 Boards or ESP32 Arduino
*
* Favoriot's HTTP Secure Certificate Validity Expires On:
* Saturday, 27 May 2023 at 14:17:12
* 
*/

#include <FavoriotHTTP.h>

const char ssid[] = "YourWiFiSSID"; // replace with your WiFi SSID
const char password[] = "YourWiFiPassword"; // replace with your WiFi password
const char deviceDeveloperId[]  = "YourDeviceDeveloperId";  // replace with your Favoriot Device Developer ID
const char deviceAccessToken[]  = "YourDeviceAccessToken";  // replace with your Favoriot Device Access Token

FavoriotHTTPS favoriot;

unsigned long previousDataIngestion = 0;
unsigned long dataIngestionInterval = 10000;

void setup() {
  Serial.begin(9600);

  // STEP 1 - Initialized Wi-Fi and IoT platform conectivity
  favoriot.begin(ssid, password, deviceAccessToken);
}

void loop() {
  
  // STEP 2 - Read data from the sensors
  byte suhu = random(22, 26);
  byte kelembapan = random(45, 55);

  // STEP 3 - Send data to Favoriot's data stream
  // data ingestion interval is 10 seconds
  if(millis() - previousDataIngestion > dataIngestionInterval){
    previousDataIngestion = millis();

    favoriot.deviceId(deviceDeveloperId);
    favoriot.dataStream("suhu", String(suhu));
    favoriot.dataStream("kelembapan", String(kelembapan));
    // add other dataStream as you wish
    favoriot.dataStreamEnd();
  }
  
}
