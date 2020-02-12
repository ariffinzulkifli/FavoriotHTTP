/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
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
    virtual void dataInterval(int wait);
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
    virtual void dataInterval(int wait);
  private:
    String _key;
    String ssid;
    String password;
    String data;
};

#endif