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
      "name": "Garage Sensor 01",
      "subscriptions": [],
      "invert": false,
      "triggers": [
          {
            "interval": 10000,
            "command": "poll"
            "offset": null
          }
      ],
      "output": {
                  "type": "TimedOutputBool",
                  "output": {
                      "invert": true,
                      "initial": true,
                      "type": "DigitalOutputPinArduino",
                      "pin": 12
                  },
                  "duration": 10000
                },
      "input": {
          "type":     "DigitalInputPinArduino",
          "pin":      13,
          "invert":   false,
          "pullup":   true
      },
      "type": distanceSensor,
      "unit": "CM",
      "constantPoll": true
    }
]})RAWSTR";


const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        CompositePeriphs,
        Device_0
};

const unsigned int Num_Json_Strings = 4;

const unsigned int Max_Json_String_Length = 817;

}

#endif
