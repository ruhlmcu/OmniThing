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

const char Device_0[] PROGMEM =
R"RAWSTR({"Devices":
[
  {
    "name": "GarageSensor",
    "subscriptions": [],
    "triggers": [
        {
            "interval": 30000,
            "command": "poll",
            "offset": 0
        }
    ],
    "input": {
      "pullup": true,
      "invert": true,
      "type": "DigitalInputPin",
      "echoPin": 13
    },
    "output": {
        "initial": true,
        "invert": false,
        "type": "DigitalOutputPin",
        "trigPin": 12
    },
    "type": "DistanceSensor",
    "timeOut": 20000,
    "constantPoll": true
  }
]})RAWSTR";
const char Device_1[] PROGMEM =
R"RAWSTR({"Devices":
[
  {
    "name": "GarageSensor2",
    "subscriptions": [],
    "triggers": [
    {
        "interval": 30000,
        "command": "poll",
        "offset": 0
    }
    ],
    "echoPin": 13,
    "trigPin": 12
    "type": "DistanceSensor",
    "timeOut": 20000,
    "constantPoll": true,
    "pullup": false
  }
]})RAWSTR";
const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        Device_0,
        Device_1
};

const unsigned int Num_Json_Strings = 4;

const unsigned int Max_Json_String_Length = 599;

}

#endif
