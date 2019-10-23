// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#include "DistanceSensor.h"
#include "OmniThing.h"
#include "Logger.h"
#include "OmniUtil.h"

#include "frozen.h"

#include <Arduino.h>
#include <string.h>



namespace omni
{
//private
void DistanceSensor::sendJsonPacket()
{
    char buffer[256] = "";
    struct json_out out = JSON_OUT_BUF(buffer, sizeof(buffer));

    json_printf(&out, "{name: \"%s\", type: \"%s\", distance: \"%s\"}", getName(), getType(), (read()?"inactive":"active"));

    LOG << buffer << Logger::endl;

    OmniThing::getInstance().sendJson(buffer);
}
//protected
//public from Ultrasonic Library Example
    DistanceSensor::DistanceSensor(unsigned short trigPin, unsigned short echoPin, unsigned long timeOut, bool constantPoll):
      tPin(trigPin), //output pin
      ePin(echoPin), //input pin
      timeout(timeOut),
      Device(constantPoll),
      echoPin(DigitalInputPin::create(ePin, false, internal_pullup)),
      trigPin(DigitalOutputPin::create(tPin, true, false))

    {

    }

    DistanceSensor::~DistanceSensor()
    {

    }
    void DistanceSensor::recvJson(const char* cmd, const char* json)
    {
        if(!strcmp(cmd, Cmd_Poll))
        {
            LOG << F("Poll triggered for ") << getType() << F(" ") << getName() << Logger::endl;
            bool val = read();
            sendJsonPacket();
        }

    }
    unsigned int DistanceSensor::read(unsigned int und)
    {
      LOG << F("DistanceSensor::read\n");
      return timing() / und / 2;  //distance by divisor
    }
    unsigned int DistanceSensor::timing()
    {
      LOG << F("DistanceSensor::timing\n");

      digitalWrite(tPin, LOW);
      delayMicroseconds(2);
      digitalWrite(tPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(tPin, LOW);

      previousMicros = micros();
      while(!digitalRead(ePin) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
      previousMicros = micros();
      while(digitalRead(ePin)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout

      return micros() - previousMicros; // duration

    }


    Device* DistanceSensor::createFromJson(const char* json)
    {
        LOG << F("DistanceSensor::createFromJson\n");

        unsigned int len = strlen(json);
        unsigned short echoPin;
        unsigned short trigPin;
        unsigned long timeOut;
        bool constantPoll;
        bool pullup = false;

        if(json_scanf(json, len, "{trigPin: %B, echoPin: %B, timeOut: %B, constantPoll: %B}", &trigPin, &echoPin,&timeOut, &constantPoll) != 4)
        {
            LOG << F("ERROR: inputs required\n");
            return nullptr;
        }

        return new DistanceSensor(trigPin, echoPin, timeOut, constantPoll);
    }
    //commands
    const char* DistanceSensor::Cmd_Poll = "poll";

    //statics
    const char* DistanceSensor::Param_Distance = "distance";

    const char* DistanceSensor::Type = "DistanceSensor";
    ObjectConfig<Device> DistanceSensor::DevConf(Type, createFromJson);
}
