# Favoriot

An [Arduino](https://arduino.cc/) library update sensors data to [Favoriot](https://platform.favoriot.com/v2/signup/FAVO7245IFBK) Data Stream using HTTP REST API.

## Compatible Hardware

This moment, the library support any [Arduino-ESP8266](https://github.com/esp8266/Arduino) development boards such as:
* [ESP8266 ESP-01](https://www.myduino.com/index.php?route=product/product&product_id=712)
* [ESP8266 NodeMCU](https://www.myduino.com/index.php?route=product/product&product_id=920)
* [Myduino IoT Training Kit](https://www.myduino.com/index.php?route=product/product&product_id=1004)

## Example Sketch

See [examples](examples) folder.

## Favoriot HTTP Arduino Library

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
byte suhu = random(22, 26);
byte kelembapan = random(45, 55);
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
Time interval updating data to Favoriot Data Stream in milliseconds.
```arduino
favoriot.dataInterval(10000);
```
* `10000` = 10 seconds

## License

This libary is [licensed](LICENSE) under the [MIT Licence](https://en.wikipedia.org/wiki/MIT_License).
