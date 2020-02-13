/*
  Favoriot.h - Library for Favoriot Data Stream.
  Created by Mohamad Ariffin Zulkifli, February 12, 2020.
  MIT License.
*/

#ifndef Favoriot_h
#define Favoriot_h

#include "Arduino.h"

class Favoriot
{
  
};

class FavoriotHTTP : public Favoriot
{
  public:
    FavoriotHTTP();
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
