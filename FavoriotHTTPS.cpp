/*
  FavoriotHTTPS.cpp - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#include "Arduino.h"
#include "FavoriotHTTPS.h"

FavoriotHTTPS::FavoriotHTTPS()
{
  
}

void FavoriotHTTPS::begin(const char* ssid, const char* password, const char* key)
{
  _key = key;

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("\nConnecting to " + String(ssid) + " ");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  delay(100);

  Serial.print("Connecting to favoriot.com using HTTPS ...");

  HTTPClient http;

  http.begin("https://apiv2.favoriot.com/", "25 20 4D 06 3C 95 69 5E 2D 25 79 59 E9 21 7B B7 6A 84 F5 5C");

  int httpCode = http.GET();

  if(httpCode > 0){
    if(httpCode == 200){
      Serial.println(" Successfully connected.");
    }
    else{
      Serial.println(" Successfully connected with error code " + String(httpCode) + "!");
    }
  }
  else{
    Serial.println(" Unsuccessful connecttion!");
  }

  http.end();
}

void FavoriotHTTPS::deviceId(const char* id)
{
  String json = "{\"device_developer_id\":\"" + String(id) + "\",\"data\":{";
  data += json;

  Serial.println("Generated Data =====================================");
}

void FavoriotHTTPS::dataStream(const char* jKey, String jValue)
{
  String json = "\"" + String(jKey) + "\":\"" + jValue + "\",";
  data += json;

  Serial.println("  " + String(jKey) +": " + jValue);
}

void FavoriotHTTPS::dataStreamEnd()
{
  data.remove(data.length() - 1);
  
  String json = "}}";
  data += json;

  Serial.println("  JSON: " + data);

  HTTPClient http;

  http.begin("https://apiv2.favoriot.com/v2/streams", "25 20 4D 06 3C 95 69 5E 2D 25 79 59 E9 21 7B B7 6A 84 F5 5C");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Apikey", _key);

  int httpCode = http.POST(data);

  if(httpCode > 0){
    String response = http.getString();
    Serial.println("  Favoriot: " + response);
  }
  else{
    Serial.println("  HTTP Error!");
  }

  data = "";

  http.end();
}
