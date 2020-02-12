/*
* This sketch has 3 main steps
* 
* 1. Initialized Favoriot connectivity
* 2. Sensors reading for data acquisition
* 3. Send data to Favoriot Data Stream
* 
*/

#include <Favoriot.h>

String ssid     = "tm15g4@unifi";
String password = "0127845327";
String apikey   = "vuOY9aVlKZOkFd6RYLW8l2Yk6KxZmVsI";

FavoriotHTTPS favoriot;

void setup() {
  Serial.begin(9600);

  // STEP 1 - Initialized Favoriot connectivity
  favoriot.begin(ssid, password, apikey);
}

void loop() {
  
  // STEP 2 - Acquire data from sensor
  byte suhu = random(22, 26);
  byte kelembapan = random(45, 55);

  // STEP 3 - Create data on Favoriot's Data Stream

  favoriot.deviceId("ESP8266@ariffinastute");
  favoriot.dataStream("suhu", String(suhu));
  favoriot.dataStream("kelembapan", String(kelembapan));
  favoriot.dataStreamEnd();
  favoriot.dataInterval(10000); // in milliseconds.
  
}