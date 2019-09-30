#ifndef OMNI_ARDUINOJSONCONFIG_H
#define OMNI_ARDUINOJSONCONFIG_H

#include <Arduino.h>

namespace omni
{
const char NetworkReceiver[] PROGMEM =
R"RAWSTR({"NetworkReceiver":
{
    "type": "NetworkManagerEsp8266", 
    "port": 1337
}})RAWSTR";

const char NetworkSender[] PROGMEM =
R"RAWSTR({"NetworkSender":
{
    "ip": "192.168.2.200", 
    "password": "yourPassword", 
    "type": "NetworkManagerEsp8266", 
    "port": 39500, 
    "ssid": "yourSSID"
}})RAWSTR";

const char CompositePeriphs[] PROGMEM =
R"RAWSTR({"CompositePeriphs":
[]})RAWSTR";

const char Device_0[] PROGMEM =
R"RAWSTR({"Devices":
[
    {
        "initial": false, 
        "name": "testSwitch", 
        "subscriptions": [
            {
                "source": "testContact", 
                "command": "toggle", 
                "event": "changed"
            }
        ], 
        "invert": false, 
        "triggers": [
            {
                "interval": 12000, 
                "command": "poll"
            }
        ], 
        "output": {
            "invert": false, 
            "initial": true, 
            "type": "DigitalOutputPinArduino", 
            "pin": 14
        }, 
        "type": "Switch"
    }
]})RAWSTR";

const char Device_1[] PROGMEM =
R"RAWSTR({"Devices":
[
    {
        "name": "testContact", 
        "triggers": [
            {
                "interval": 12000, 
                "command": "poll", 
                "offset": 3000
            }
        ], 
        "invert": false, 
        "input": {
            "pullup": true, 
            "invert": false, 
            "type": "DigitalInputPinArduino", 
            "pin": 4
        }, 
        "type": "ContactSensor", 
        "constantPoll": true
    }
]})RAWSTR";

const char Device_2[] PROGMEM =
R"RAWSTR({"Devices":
[
    {
        "input": {
            "minVoltage": 0, 
            "type": "AnalogInputPinArduino", 
            "maxVoltage": 3.3, 
            "pin": 17
        }, 
        "subscriptions": [
            {
                "source": "testContact", 
                "command": "poll", 
                "event": "closed"
            }
        ], 
        "type": "VoltageMeasurement", 
        "name": "testVoltage", 
        "triggers": [
            {
                "interval": 12000, 
                "command": "poll", 
                "offset": 6000
            }
        ]
    }
]})RAWSTR";

const char Device_3[] PROGMEM =
R"RAWSTR({"Devices":
[
    {
        "output": {
            "invert": false, 
            "initial": true, 
            "type": "DigitalOutputPinArduino", 
            "pin": 5
        }, 
        "subscriptions": [
            {
                "source": "testContact", 
                "command": "push", 
                "event": "changed"
            }
        ], 
        "type": "Momentary", 
        "name": "testMomentary", 
        "triggers": [
            {
                "interval": 12000, 
                "command": "poll", 
                "offset": 9000
            }
        ]
    }
]})RAWSTR";



const char* const Config_Json_Strings[] PROGMEM = {
        NetworkReceiver,
        NetworkSender,
        CompositePeriphs,
        Device_0,
        Device_1,
        Device_2,
        Device_3
};

const unsigned int Num_Json_Strings = 7;

const unsigned int Max_Json_String_Length = 615;

}

#endif
