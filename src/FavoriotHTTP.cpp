/*
  FavoriotHTTP.cpp - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#include "Arduino.h"
#include "FavoriotHTTP.h"

#if ESP32 || ARDUINO_ARCH_RP2040
#include <FavoriotRootCA.h>
#endif

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

  Serial.print(" connected.");

  #if ESP8266
  String controller = "ESP8266";
  #elif ESP32
  String controller = "ESP32";
  #elif ARDUINO_ARCH_RP2040
  String controller = "Raspberry Pi Pico";
  #endif
  
  Serial.println();
  Serial.print(controller + " Local IP Address: ");
  Serial.println(WiFi.localIP());

  delay(100);

  Serial.print("Connecting to favoriot.com using HTTP ...");
  
  #if ESP8266

  const uint8_t httpsFingerprint[20] = {0xB4, 0x90, 0xEA, 0xFE, 0xFC, 0xCE, 0x8D, 0x78, 0xCC, 0x92, 0xAD, 0x48, 0x7D, 0xE8, 0xDE, 0xFA, 0x0A, 0xA3, 0x91, 0x3C};

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    
  client->setFingerprint(httpsFingerprint);

  HTTPClient https;

  https.begin(*client, "https://apiv2.favoriot.com/");

  int httpCode = https.GET();

  if(httpCode > 0){

    String httpResponse = https.getString();
    if(httpCode == 200){
      Serial.println(" Successfully connected.");
    }
    else{
      Serial.println(" Successfully connected with error code " + String(httpCode) + ": " + httpResponse + "!");
    }
  }
  else{
    Serial.println(" Unsuccessful connection!");
  }

  https.end();

  #elif ESP32 || ARDUINO_ARCH_RP2040
  WiFiClientSecure *clientBegin = new WiFiClientSecure;

  if(clientBegin) {
    clientBegin -> setCACert(favoriotRootCACertificate);
    {
      HTTPClient https;
    
      https.begin(*clientBegin, "https://apiv2.favoriot.com/");

      int httpCode = https.GET();

      if(httpCode > 0){

        String httpResponse = https.getString();
        if(httpCode == 200){
          Serial.println(" Successfully connected.");
        }
        else{
          Serial.println(" Successfully connected with error code " + String(httpCode) + ": " + httpResponse + "!");
        }
      }
      else{
        Serial.println(" Unsuccessful connection!");
      }

      https.end();
    }
    delete clientBegin;
  }
  else{
    Serial.println(" Unsuccessful HTTPS client connection!");
  }

  #endif

  Serial.println();

  dataCount = 0;
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

  Serial.println("  #" + String(dataCount++) + " " + String(jKey) +": " + jValue);
}

void FavoriotHTTP::dataStreamEnd()
{
  data.remove(data.length() - 1);
  
  String json = "}}";
  data += json;

  Serial.println("  Total Count of Data Generated: " + String(dataCount));
  Serial.println("  Data in JSON format: " + data);

  #if ESP8266
  WiFiClient client;
  HTTPClient http;

  http.begin(client, "http://apiv2.favoriot.com/v2/streams");

  #elif ESP32 || ARDUINO_ARCH_RP2040
  HTTPClient http;

  http.begin("http://apiv2.favoriot.com/v2/streams");

  #endif

  http.addHeader("Content-Type", "application/json");
  http.addHeader("Apikey", _key);

  int httpCode = http.POST(data);

  if(httpCode > 0){
    Serial.print("> HTTP Request: ");
    
    httpCode == 201 ? Serial.print("Success, ") : Serial.print("Error, ");
    Serial.println(http.getString());
  }
  else{
    Serial.println("> HTTP Request Connection Error!");
  }

  http.end();

  data = "";
  dataCount = 0;

  Serial.println();
}

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

  Serial.print(" connected.");

  #if ESP8266
  String controller = "ESP8266";
  #elif ESP32
  String controller = "ESP32";
  #elif ARDUINO_ARCH_RP2040
  String controller = "Raspberry Pi Pico";
  #endif
  
  Serial.println();
  Serial.print(controller + " IP Address: ");
  Serial.println(WiFi.localIP());

  delay(100);

  Serial.print("Connecting to favoriot.com using HTTPS ...");
  
  #if ESP8266
  const uint8_t httpsFingerprint[20] = {0xB4, 0x90, 0xEA, 0xFE, 0xFC, 0xCE, 0x8D, 0x78, 0xCC, 0x92, 0xAD, 0x48, 0x7D, 0xE8, 0xDE, 0xFA, 0x0A, 0xA3, 0x91, 0x3C};

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    
  client->setFingerprint(httpsFingerprint);

  HTTPClient https;

  https.begin(*client, "https://apiv2.favoriot.com/");

  int httpCode = https.GET();

  if(httpCode > 0){

    String httpResponse = https.getString();
    if(httpCode == 200){
      Serial.println(" Successfully connected.");
    }
    else{
      Serial.println(" Successfully connected with error code " + String(httpCode) + ": " + httpResponse + "!");
    }
  }
  else{
    Serial.println(" Unsuccessful connection!");
  }

  https.end();

  #elif ESP32 || ARDUINO_ARCH_RP2040
  WiFiClientSecure *clientBegin = new WiFiClientSecure;

  if(clientBegin) {
    clientBegin -> setCACert(favoriotRootCACertificate);
    {
      HTTPClient https;
    
      https.begin(*clientBegin, "https://apiv2.favoriot.com/");

      int httpCode = https.GET();

      if(httpCode > 0){

        String httpResponse = https.getString();
        if(httpCode == 200){
          Serial.println(" Successfully connected.");
        }
        else{
          Serial.println(" Successfully connected with error code " + String(httpCode) + ": " + httpResponse + "!");
        }
      }
      else{
        Serial.println(" Unsuccessful connection!");
      }

      https.end();
    }
    delete clientBegin;
  }
  else{
    Serial.println(" Unsuccessful HTTPS client connection!");
  }

  #endif

  Serial.println();

  dataCount = 0;
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

  Serial.println("  #" + String(dataCount++) + " " + String(jKey) +": " + jValue);
}

void FavoriotHTTPS::dataStreamEnd()
{
  data.remove(data.length() - 1);
  
  String json = "}}";
  data += json;

  Serial.println("  Total Count of Data Generated: " + String(dataCount));
  Serial.println("  Data in JSON format: " + data);

  #if ESP8266
  const uint8_t httpsFingerprint[20] = {0xB4, 0x90, 0xEA, 0xFE, 0xFC, 0xCE, 0x8D, 0x78, 0xCC, 0x92, 0xAD, 0x48, 0x7D, 0xE8, 0xDE, 0xFA, 0x0A, 0xA3, 0x91, 0x3C};

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    
  client->setFingerprint(httpsFingerprint);

  HTTPClient https;

  https.begin(*client, "https://apiv2.favoriot.com/v2/streams");

  https.addHeader("Content-Type", "application/json");
  https.addHeader("Apikey", _key);

  int httpCode = https.POST(data);

  if(httpCode > 0){
    Serial.print("> HTTPS Request: ");
    
    httpCode == 201 ? Serial.print("Success, ") : Serial.print("Error, ");
    Serial.println(https.getString());
  }
  else{
    Serial.println("> HTTPS Request Connection Error!");
  }

  https.end();

  #elif ESP32 || ARDUINO_ARCH_RP2040
  WiFiClientSecure *client = new WiFiClientSecure;
  
  if(client) {
    client -> setCACert(favoriotRootCACertificate);
    {
      
      HTTPClient https;
    
      https.begin(*client, "https://apiv2.favoriot.com/v2/streams");
    
      https.addHeader("Content-Type", "application/json");
      https.addHeader("Apikey", _key);
      
      int httpCode = https.POST(data);
    
      if(httpCode > 0){
        Serial.print("> HTTPS Request: ");
        
        httpCode == 201 ? Serial.print("Success, ") : Serial.print("Error, ");
        Serial.println(https.getString());
      }
      else{
        Serial.println("> HTTPS Request Connection Error!");
      }
    
      https.end();
      Serial.println();
    }

    delete client;
  }

  else {
    Serial.println("Unable to create HTTPS client");
    Serial.println();
  }

  #endif

  data = "";
  dataCount = 0;

  Serial.println();
}
