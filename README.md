# ESP8266_MAX7219_Clock
- ESP8266_MAX7219_Clock is a digital clock project based on the ESP8266 microcontroller and a MAX7219-driven LED matrix display. The system displays real-time clock information on an LED matrix and synchronizes time via an NTP server
- The project is designed with a modular architecture, allowing easy expansion with additional animations. 

## Features
- Synchronizes time via an NTP server.
- Update parameters via UDP.
- Displays information on the LED matrix modules.
- Parameters are saved in EEPROM and can be reused after a restart.

https://github.com/user-attachments/assets/d4e5b750-0d1a-4728-a880-18d69df8f986

## Hardware Requirements
- Esp8266-12E
- Module Led Matrix 8 x 32(Max7912)

### Max7912
- Link: https://www.analog.com/media/en/technical-documentation/data-sheets/max7219-max7221.pdf

<p align="center">
    <img src="include/image/max7912/Typical Application Circuit.png" width="400"><br>
    <em>Fig 1.Typical Application Circuit</em>
</p>

- It uses SPI to send data to the MAX7219, allowing control of eight 7-segment modules, which together are equivalent to an 8×8 LED matrix.

<p align="center">
    <img src="include/image/max7912/Functional Diagram.png" width="400"><br>
    <em>Fig 2.Functional Diagram</em>
</p>

- The MAX7219 contains registers that store the necessary parameters for normal operation.

<p align="center">
    <img src="include/image/max7912/Serial-Data Format (16 Bits).png" width="400"><br>
    <em>Fig 3.Serial-Data Format (16 Bits)</em>
</p>

- Based on Figures 2 and 3, it can be seen that the MAX7219 receives the higher bits first, followed by the lower bits (LSB → MSB).

### Esp8266

<p align="center">
    <img src="include/image/esp8266/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png" width="400"><br>
    <em>Fig 4.Esp8266 Gpio (16 Bits)</em>
</p>

- In this project, HSPI is used to transmit messages to the MAX7219.

## Setup

### Hardware Connections


| MAX7219 Pin | ESP8266 Pin|
|-------------|------------|
| VCC         | 5V (Vin)   |
| GND         | GND        |
| DIN         | D7 (GPIO13)|
| CLK         | D5 (GPIO14)|
| CS / LOAD   | D2 (GPIO4) |


### Configuration
- You need to modify the following parameters to complete the initial setup:

#### Wifi Config

- The following parameters need to be modified in the file "main.cpp":
    + `AP`: The ESP creates an access point, allowing users to modify and control the ESP8266.
    + `Station`: It also connects to WiFi to synchronize the time with an NTP server.

- Note: If the ESP8266 fails to connect to WiFi for any reason, the user can access the ESP's access point to modify the station settings. After updating, the device will reset and attempt to connect to the new station.

```cpp
#define Ap_Name ""
#define Ap_Psk ""

#define Station_Name ""
#define Station_Psk ""
```

#### NTP Server
- The following parameters need to be modified in the file "time_rtc_custom.h":
    + `UTC_Time` : Time zone offset in seconds (e.g., `(7*3600)` for UTC+7)  
    + `DaylightOffset` : Daylight Saving Time offset in seconds (`0` if not used)  
    + `Server_One` : Primary NTP server  
    + `Server_Two` : Secondary NTP server (fallback)

```cpp
#define UTC_Time (7 * 3600)
#define DaylightOffset 0
#define Server_One "pool.ntp.org"
#define Server_Two "time.nist.gov"
```
#### UDP Setup

- The following parameters need to be modified in the file "wifi_custom.h":
    + `Ip` : ESP8266 AP IP  
    + `Gateway` : AP Gateway IP  
    + `Subnet` : AP Subnet mask  
    + `Port` : UDP port

```cpp
#define Ip IPAddress(192, 168, 4, 1)
#define Gateway IPAddress(192, 168, 4, 1)
#define Subnet IPAddress(255, 255, 255, 0)
#define Port 5312 
```
#### Add Runtime effects

Note: If you want to add runtime effects, please follow the instructions; otherwise, you can skip this step.

Step 1:
- The following parameters need to be modified in the file "watch_data_in_flash.cpp":
    + Please update the variable name. Requirement: 
    + It must be 8-bit and the size must be divisible by 8.

```cpp
const uint8 name[] PROGMEM = {};
```

Step 2:
- The following parameters need to be modified in the file "watch_data_in_flash.cpp":

- Note: Add the newly added variable to the array below as shown.

```cpp
const DecorData varibleDecor[] = {
    { pixelDecorStyle1, sizeof(pixelDecorStyle1) / sizeof(pixelDecorStyle1[0]) / ROW_SIZE},
    { pixelDecorStyle2, sizeof(pixelDecorStyle2) / sizeof(pixelDecorStyle2[0]) / ROW_SIZE},
    { pixelDecorStyle3, sizeof(pixelDecorStyle3) / sizeof(pixelDecorStyle3[0]) / ROW_SIZE},
    { pixelDecorStyle4, sizeof(pixelDecorStyle4) / sizeof(pixelDecorStyle4[0]) / ROW_SIZE},
    { pixelDecorStyle5, sizeof(pixelDecorStyle5) / sizeof(pixelDecorStyle5[0]) / ROW_SIZE},
};
```

## Control

### Message

#### Brightness
- Set the LED matrix brightness (Command = 4). Value range: 0 (lowest) to 15 (highest).

```json
{
  "Brightness": "15",
  "Command": 4
}
```

#### Access Point
- Configure the ESP8266 Access Point name and password (Command = 1).

```json
{
  "AP Psk": "12345678",
  "Command": 1,
  "AP Name": "watch"
}
```

#### Station
- Configure the ESP8266 Station (WiFi) name and password (Command = 0).

```json
{
  "Station Psk": "12345678",
  "Command": 0,
  "Station Name": "watch"
}
```

#### Time Step Decor Element
- Set the update interval for the decor element animation in milliseconds (Command = 2).

```json
{
  "Time Step Decor Element": 100,
  "Command": 2
}
```

#### Time Step Time Element
- Set the update interval for the time element display in milliseconds (Command = 3).

```json
{
  "Time Step Time Element": 100,
  "Command": 3
}
```

#### Message reply
- Replies with current settings when a message is received.

```json
{
  "Brightness": 3,
  "Time Step Decor Element": 200,
  "Time Step Time Element": 100,
  "Station Name": "",
  "Station Psk": "",
  "AP Name": "",
  "AP Psk": ""
}
```

### APP Controller
- Coming soon. Will be updated later.
 
