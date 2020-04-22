# Favoriot

An [Arduino](https://arduino.cc/) library update sensors data to [Favoriot](https://platform.favoriot.com/v2/signup/FAVO7245IFBK) Data Stream using HTTP REST API.

## Compatible Hardware

This moment, the library support any [Arduino-ESP32](https://github.com/espressif/arduino-esp32) and [Arduino-ESP8266](https://github.com/esp8266/Arduino) development boards such as:
* [ESP8266 ESP-01](https://www.myduino.com/index.php?route=product/product&product_id=712)
* [ESP8266 NodeMCU](https://www.myduino.com/index.php?route=product/product&product_id=920)
* [Myduino IoT Training Kit](https://www.myduino.com/index.php?route=product/product&product_id=1004)

## Example Sketch

See [examples](examples) folder.
* [FavoriotHTTP.ino](examples/FavoriotHTTP/FavoriotHTTP.ino) - using `delay` function for data interval update
* [FavoriotHTTPS.ino](examples/FavoriotHTTPS/FavoriotHTTPS.ino) - using `millis` function for data interval update

## Favoriot Library Requirements

1. Favoriot `Device Access Token`. Learn how to generate your Device Access Token on [Favoriot Documentation](https://platform.favoriot.com/tutorial/v2/#device-access-token)

2. Favoriot `Device Developer ID`. Get your Device Developer ID from [Favoriot, Device's Page](https://platform.favoriot.com/v2/iot/devices). e.g. `deviceDefault@username`

## Favoriot Arduino Library

### Include Library and variable declaration

```arduino
#include <Favoriot.h>
```
Declaration of `ssid`, `password` and `apikey`

```arduino
String ssid     = "YourWiFiSSID";           // replace with your WiFi SSID
String password = "YourWiFiPassword";       // replace with your WiFi password
String apikey   = "YourDeviceAccessToken";  // replace with your Favoriot Device Access Token
```
### Favoriot Class

Using HTTP to connect to Favoriot IoT platform

```arduino
FavoriotHTTP favoriot;
```

Using HTTPS to connect to Favoriot IoT platform

```arduino
FavoriotHTTPS favoriot;
```

### Begin

Initialized connection to Favoriot IoT platform

```arduino
favoriot.begin(ssid, password, apikey); 
```

### Update sensors data to Favoriot Data Stream

Example of data acquisition

```arduino
byte suhu = random(22, 26);         // random function to generate value between 22-26
byte kelembapan = random(45, 55);   // random function to generate value between 45-55
```

Declare Favoriot Device Developer ID

```arduino
favoriot.deviceId("DeviceDeveloperId");
```
Start the sequence of Favoriot Data Stream with declared data. 

```arduino
favoriot.dataStream("suhu", String(suhu));
favoriot.dataStream("kelembapan", String(kelembapan));
```

End the sequence of Favoriot Data Stream.

```arduino
favoriot.dataStreamEnd();
```
Time interval updating data to Favoriot Data Stream by using `delay` function.
```arduino
delay(10000); // value in milliseconds
```
* `10000` = 10 seconds

## License

This libary is [licensed](LICENSE) under the [MIT Licence](https://en.wikipedia.org/wiki/MIT_License).
