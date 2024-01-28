# esp8266 DFUN SPM91 smartmeter

The esp8266 code reads the modbus smartmeter DFUN SPM91 real-time data with registers(0x03 RO)

## Required hardware

- esp8266 D1 mini or similar
- MAX3485
- DFUN SPM91 smartmeter

Connection:

D1 mini -> MAX3485

| D1 mini | MAX3485 |
| ------- | ------- |
| D1 / RX | RO      |
| D2 / TX | DI      |
| 3V3     | VCC     |
| GND     | GND     |

## Setup

Setup wifi in main.cpp:

```cpp
const char *ssid = "<SSID>";         // Set Your WIFI SSID
const char *password = "<PASSWORD>"; // Set Your WIFI Password
```
