```
   __  ___     _                   __    ______        __             __          _       
  /  |/  /_ __(_)__ _  _____ ___  / /_  /_  __/__ ____/ /  ___  ___  / /__  ___ _(_)__ ___
 / /|_/ / // / / _ \ |/ / -_) _ \/ __/   / / / -_) __/ _ \/ _ \/ _ \/ / _ \/ _ `/ / -_|_-<
/_/  /_/\_, /_/_//_/___/\__/_//_/\__/   /_/  \__/\__/_//_/_//_/\___/_/\___/\_, /_/\__/___/
       /___/                                                              /___/           
iot.embedded.ai.connectivity.training.solutions ==========================================

https://myduino.com
ariffin@myduino.com
```

<p align="right">
    <a href="https://myduino.com"><img src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fariffinzulkifli%2FFavoriotHTTP&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false"/></a>
</p>

# FavoriotHTTP Arduino Library

A simple [Arduino](https://arduino.cc/) library for ESP8266, ESP32 microcontrollers and Raspberry Pi Pico W to update sensors data to [Favoriot's](https://platform.favoriot.com/) IoT platform.

Support both HTTP and Secure HTTPS connection.

Alert: Currently, the secure HTTPS connection for Raspberry Pico W is unstable. If you want to make stable secure HTTPS connection with Raspberry Pico W, it would better to program the RP2040 using [Circuitpython](https://circuitpython.org/board/raspberry_pi_pico_w/).

## Compatible Hardware

At them moment, the library support any [Arduino-ESP32](https://github.com/espressif/arduino-esp32) and [Arduino-ESP8266](https://github.com/esp8266/Arduino) and [Arduino-Pico-W](https://github.com/earlephilhower/arduino-pico) development boards such as:
* [ESP8266 ESP-01](https://myduino.com/product/key-098/)
* [ESP8266 NodeMCU](https://myduino.com/product/jhs-031/)
* [Myduino IoT Training Kit](https://myduino.com/product/myd-002/)
* [ESP32 NodeMCU](https://shopee.com.my/NodeMCU-ESP32-Arduino-Micropython-WiFi-Bluetooth-Development-Board-CP2102-USB-Driver-i.132184430.8469749720)
* [Hibiscus Sense](https://myduino.com/product/myd-036/)
* [Raspberry Pi Pico W](https://my.cytron.io/p-raspberry-pi-pico-wireless-board-smd-presoldered-headers)

## Example Sketch

See [examples](examples) folder.
* [FavoriotHTTP.ino](examples/FavoriotHTTP/FavoriotHTTP.ino)
* [FavoriotHTTPS.ino](examples/FavoriotHTTPS/FavoriotHTTPS.ino)

## Favoriot Library Requirements

1. Favoriot `Device Access Token`. Learn how to generate your Device Access Token on [Favoriot Documentation](https://platform.favoriot.com/tutorial/v2/#device-access-token)

2. Favoriot `Device Developer ID`. Get your Device Developer ID from [Favoriot, Device's Page](https://platform.favoriot.com/v2/iot/devices). e.g. `deviceDefault@username`

## Favoriot Arduino Library

### Include Library and variable declaration

A library to rule HTTP and HTTPS connection to Favoriot's data stream.

```arduino
#include <FavoriotHTTP.h>
```

Declaration of `ssid`, `password` , `deviceAccessToken` and `deviceDeveloperId`

```arduino
char ssid[]     = "YourWiFiSSID"; // replace with your WiFi SSID
char password[] = "YourWiFiPassword"; // replace with your WiFi password
const char deviceDeveloperId[]  = "YourDeviceDeveloperId";  // replace with your Favoriot Device Developer ID
char deviceAccessToken[]   = "YourDeviceAccessToken";  // replace with your Favoriot Device Access Token
```
### Favoriot Class

Class for HTTP connection.

```arduino
FavoriotHTTP favoriot;
```

Class for Secure HTTPS connection.

```arduino
FavoriotHTTPS favoriot;
```

### Begin

Initialized connection to Favoriot IoT platform

```arduino
favoriot.begin(ssid, password, deviceAccessToken); 
```

### Update sensors data to Favoriot Data Stream

Example of data acquisition

```arduino
byte suhu = random(22, 26);         // random function to generate value between 22-26
byte kelembapan = random(45, 55);   // random function to generate value between 45-55
```

Declare Favoriot Device Developer ID

```arduino
favoriot.deviceId(deviceDeveloperId);
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

Time interval updating data to Favoriot Data Stream by using `millis` function.
```arduino
if(millis() - previousMillis > 10000){
    previousMillis = millis();

    favoriot.deviceId(deviceDeveloperId);
    favoriot.dataStream("suhu", String(suhu));
    favoriot.dataStream("kelembapan", String(kelembapan));
    favoriot.dataStreamEnd();

  }
```
* `10000` = 10 seconds

## License

This libary is [licensed](LICENSE) under the [MIT Licence](https://en.wikipedia.org/wiki/MIT_License).
