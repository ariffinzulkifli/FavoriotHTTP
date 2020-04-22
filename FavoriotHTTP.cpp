/*
  FavoriotHTTP.cpp - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#include "Arduino.h"
#include "FavoriotHTTP.h"

FavoriotHTTP::FavoriotHTTP()
{
  
}

void FavoriotHTTP::begin(const char* ssid, const char* password, const char* key)
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

  Serial.print("Connecting to favoriot.com using HTTP ...");

  HTTPClient http;

  http.begin("http://apiv2.favoriot.com/");

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

void FavoriotHTTP::deviceId(const char* id)
{
  String json = "{\"device_developer_id\":\"" + String(id) + "\",\"data\":{";
  data += json;

  Serial.println("Generated Data =====================================");
}

void FavoriotHTTP::dataStream(const char* jKey, String jValue)
{
  String json = "\"" + String(jKey) + "\":\"" + jValue + "\",";
  data += json;

  Serial.println("  " + String(jKey) +": " + jValue);
}

void FavoriotHTTP::dataStreamEnd()
{
  data.remove(data.length() - 1);
  
  String json = "}}";
  data += json;

  Serial.println("  JSON: " + data);

  HTTPClient http;

  http.begin("http://apiv2.favoriot.com/v2/streams");
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
