/*
  Favoriot.cpp - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#include "Arduino.h"
#include "Favoriot.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

FavoriotHTTP::FavoriotHTTP() : Favoriot()
{
  
}

void FavoriotHTTP::begin(String ssid, String password, String key)
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

void FavoriotHTTP::deviceId(String id)
{
  String json = "{\"device_developer_id\":\"" + id + "\",\"data\":{";
  data += json;

  Serial.println("Generated Data =====================================");
}

void FavoriotHTTP::dataStream(String jKey, String jValue)
{
  String json = "\"" + jKey + "\":\"" + jValue + "\",";
  data += json;

  Serial.println("  " + jKey +": " + jValue);
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

FavoriotHTTPS::FavoriotHTTPS() : Favoriot()
{

}

void FavoriotHTTPS::begin(String ssid, String password, String key)
{
  _key = key;

  Serial.begin(9600);

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

void FavoriotHTTPS::deviceId(String id)
{
  String json = "{\"device_developer_id\":\"" + id + "\",\"data\":{";
  data += json;

  Serial.println("Generated Data =====================================");
}

void FavoriotHTTPS::dataStream(String jKey, String jValue)
{
  String json = "\"" + jKey + "\":\"" + jValue + "\",";
  data += json;

  Serial.println("  " + jKey +": " + jValue);
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
