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
    "name": "GarageSensor2",
    "subscriptions": [],
    "triggers": [
    {
        "interval": 30000,
        "command": "poll",
        "offset": 0
    }
    ],
    "echoPin": 05,
    "trigPin": 04,
    "type": "DistanceSensor",
    "timeOut": 20000,
    "pullup": false
  }
]})RAWSTR";
const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        Device_0
};

const unsigned int Num_Json_Strings = 3;

const unsigned int Max_Json_String_Length = 599;

}

#endif
