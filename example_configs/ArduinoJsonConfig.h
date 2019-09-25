#ifndef OMNI_ARDUINOJSONCONFIG_H
#define OMNI_ARDUINOJSONCONFIG_H

#include <Arduino.h>

namespace omni
{
const char NetworkReceiver[] PROGMEM =
R"RAWSTR({"NetworkReceiver":
{
    "password": null, 
    "type": "NetworkManagerEsp8266", 
    "port": 1337, 
    "ssid": null
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
[
    {
        "triggerPin": 12, 
        "name": "Garage Sensor 01", 
        "echoPin": 13, 
        "invert": true, 
        "pullup": true, 
        "type": "DistanceSensor"
    }
]})RAWSTR";



const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        CompositePeriphs
};

const unsigned int Num_Json_Strings = 3;

const unsigned int Max_Json_String_Length = 210;

}

#endif
