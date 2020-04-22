/*
  Favoriot.h - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#ifndef Favoriot_h
#define Favoriot_h

#include "Arduino.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#elif defined ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif

class Favoriot
{
  
};

class FavoriotHTTP : public Favoriot
{
  public:
    FavoriotHTTP();
    virtual void begin(const char* key, const char* ssid, const char* password);
    virtual void deviceId(const char* key);
    virtual void dataStream(const char* key, String value);
    virtual void dataStreamEnd();
  private:
    const char* _key;
    const char* ssid;
    const char* password;
    String data;
};

class FavoriotHTTPS : public Favoriot
{
  public:
    FavoriotHTTPS();
    virtual void begin(String key, String ssid, String password);
    virtual void deviceId(String key);
    virtual void dataStream(String key, String value);
    virtual void dataStreamEnd();
  private:
    String _key;
    String ssid;
    String password;
    String data;
};

#endif
