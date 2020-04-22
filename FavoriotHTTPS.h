/*
  FavoriotHTTPS.h - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#ifndef FavoriotHTTPS_h
#define FavoriotHTTPS_h

#include "Arduino.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#elif defined ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif

class FavoriotHTTPS
{
  public:
    FavoriotHTTPS();
    void begin(const char* key, const char* ssid, const char* password);
    void deviceId(const char* key);
    void dataStream(const char* key, String value);
    void dataStreamEnd();
  private:
    const char* _key;
    const char* ssid;
    const char* password;
    String data;
};

#endif
