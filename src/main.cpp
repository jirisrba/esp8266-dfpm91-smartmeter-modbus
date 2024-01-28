/*
DFUN SPM91 Real-time data registers(0x03 RO)

Smartmeter modbus data in case of negative load:

V = 238
I = 100 [ 100 0 ]
W = -9 [ 65440 65535 ]

*/

#include <ESP8266WiFi.h>
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
#include "struct.h"

#define RX_PIN D1
#define TX_PIN D2
#define BAUDRATE 9600
#define SLAVE_ID 1

#define FIRST_REG 0
#define REG_COUNT 12

SoftwareSerial S(RX_PIN, TX_PIN);

ModbusRTU rtu;

/// WIFI CONFIG ///
const char *ssid = "<SSID>";         // Set Your WIFI SSID
const char *password = "<PASSWORD>"; // Set Your WIFI Password

struct dfun_meter_data handleData(uint16_t res[REG_COUNT])
{
  struct dfun_meter_data data;

  data.voltage = res[2] / 100;
  data.current = (res[4] << 16 | res[3]);
  data.active_power = (res[6] << 16 | res[5]) / 10;
  data.frequency = res[11] / 100;

  return data;
}

bool cb(Modbus::ResultCode event, uint16_t transactionId, void *data)
{ // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS)
  {
    Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
  }
  return true;
}

void setup()
{
  Serial.begin(9600);
  S.begin(BAUDRATE, SWSERIAL_8N1);

  WiFi.begin(ssid, password); // Connect to your WiFi router

  while (WiFi.status() != WL_CONNECTED)
  { // Wait for connection
    delay(500);
  }

  rtu.begin(&S);
  rtu.master();
}

void loop()
{
  uint16_t res[REG_COUNT];

  rtu.readHreg(SLAVE_ID, FIRST_REG, res, REG_COUNT, cb); // Send Read Hreg from Modbus Server
  while (rtu.slave())
  { // Check if transaction is active
    rtu.task();
    delay(10);
  }

  struct dfun_meter_data data = handleData(res);

  Serial.println(data.voltage);
  Serial.println(data.current);
  Serial.println(data.active_power);

  delay(1000);
}
