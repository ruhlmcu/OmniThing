#ifndef OMNI_ARDUINOJSONCONFIG_H
#define OMNI_ARDUINOJSONCONFIG_H

#include <Arduino.h>

namespace omni
{
const char NetworkReceiver[] PROGMEM =
R"RAWSTR({"NetworkReceiver":
{
    "password": "Toyota3879",
    "type": "NetworkManagerEsp8266",
    "port": 8090,
    "ssid": "ruhlman"
}})RAWSTR";

const char NetworkSender[] PROGMEM =
R"RAWSTR({"NetworkSender":
{
    "ip": "192.168.1.30",
    "password": "Toyota3879",
    "type": "NetworkManagerEsp8266",
    "port": 39500,
    "ssid": "ruhlman"
}})RAWSTR";

const char CompositePeriphs[] PROGMEM =
R"RAWSTR({"CompositePeriphs":
[]})RAWSTR";

const char Device_0[] PROGMEM =
R"RAWSTR({"Devices":
[
  {
      "name": "GarageSensor01",
      "subscriptions": [],
      "input": {
          "type":     "DigitalInputPinArduino",
          "pin":      13,
          "invert":   false,
          "pullup":   true
      }
      "output": {
          "type": "DigitalOutputPinArduino",
          "pin": 12,
          "invert": false,
          "initial": true
      },
      "type": "distanceSensor",
      "constantPoll": true,
      "triggers": [
        {
          "interval": 10000,
          "command": "poll",
          "offset": 0
        }
      ]
    }
]})RAWSTR";



const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        CompositePeriphs,
        Device_0
};

const unsigned int Num_Json_Strings = 4;

const unsigned int Max_Json_String_Length = 599;

}

#endif
