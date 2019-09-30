#include "DigitalOutputPinArduinoTimed.h"

#include <Arduino.h>
#include <string.h>
#include "frozen.h"

namespace omni
{
//private
    DigitalOutputPinArduinoTimed* DigitalOutputPinArduinoTimed::createFromJson(const char* json)
    {
        unsigned int len = strlen(json);

        unsigned short pin;
        bool initial;
        bool invert;
        unsigned long duration;

        if(json_scanf(json, len, "{pin: %hu, initial: %B, invert: %B}", &pin, &initial, &invert) != 3)
        {
            return nullptr;
        }

        return new DigitalOutputPinArduinoTimed(pin, initial, invert, duration);
    }

//protected
    void DigitalOutputPinArduinoTimed::writePin(bool b)
    {
        digitalWrite(getPin(), b);
    }

//public
    DigitalOutputPinArduinoTimed::DigitalOutputPinArduinoTimed(unsigned short pin, bool initialVal, bool invertLogic, unsigned long duration):
        DigitalOutputPinTimed(pin, initialVal, invertLogic, duration)
    {
        configure();
        writeBool(initialVal);
    }

    DigitalOutputPinArduinoTimed::~DigitalOutputPinArduinoTimed()
    {

    }

    bool DigitalOutputPinArduinoTimed::configure()
    {
        pinMode(getPin(), OUTPUT);
        return true;
    }

    OutputVoid* DigitalOutputPinArduinoTimed::createVoidFromJson(const char* json)
    {
        return createFromJson(json);
    }

    OutputBool* DigitalOutputPinArduinoTimed::createBoolFromJson(const char* json)
    {
        return createFromJson(json);
    }

    const char* DigitalOutputPinArduinoTimed::Type = "DigitalOutputPinArduinoTimed";
    ObjectConfig<OutputVoid> DigitalOutputPinArduinoTimed::OutputVoidConf(Type, createVoidFromJson);
    ObjectConfig<OutputBool> DigitalOutputPinArduinoTimed::OutputBoolConf(Type, createBoolFromJson);

}
