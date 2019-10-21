// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#include "DistanceSensor.h"

#include <Arduino.h>
#include <string.h>
#include "frozen.h"
#include "OmniThing.h"

#include "Logger.h"

namespace omni
{
//private
  void DistanceSensor::sendJsonPacket()
  {
      char buffer[100] = "";
      struct json_out out = JSON_OUT_BUF(buffer, sizeof(buffer));

      json_printf(&out, "{name: \"%s\", type: \"%s\", distance: \"%s\"}", getName(), getType(), read());

      LOG << buffer << Logger::endl;

      OmniThing::getInstance().sendJson(buffer);
  }
//protected
//public from Ultrasonic Library Example
    DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut, bool constantPoll):
    Device(constantPoll),
    trig(trigPin),
    echo(echoPin),
    timeout(timeOut)
      {
      LOG << F("Made it here #1\n");
      threePins = trig == echo ? true : false;
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
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
            if(val != m_bLastVal)
            {
                emit(Event_Changed);
            }
            m_bLastVal = val;
            sendJsonPacket();
        }

    }
    void DistanceSensor::run()
    {
        bool val = read();
        if(val != m_bLastVal)
        {
            emit(Event_Changed);

            if(val)
                emit(Event_Active);
            else
                emit(Event_Inactive);

            sendJsonPacket();
        }
        m_bLastVal = val;
    }

    void DistanceSensor::init()
    {
        m_bLastVal = read();
        sendJsonPacket();
    }
    unsigned int DistanceSensor::read(uint8_t und)
    {
      LOG << F("Made it here #3\n");
      return timing() / und / 2;  //distance by divisor
    }
    unsigned int DistanceSensor::timing()
    {
      LOG << F("Made it here #2\n");
      if (threePins)
        pinMode(trig, OUTPUT);

      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      if (threePins)
        pinMode(trig, INPUT);

      previousMicros = micros();
      while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
      previousMicros = micros();
      while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout

      return micros() - previousMicros; // duration

    }


    Device* DistanceSensor::createFromJson(const char* json)
    {
//        bool invert;
        bool constantPoll;

        unsigned int len = strlen(json);
        json_token t;

        if(json_scanf(json, len, "{trigPin: %T, echoPin: %B, timeOut: %B}", &t, &constantPoll) != 3)
        {
            return nullptr;
        }

        auto input = OmniThing::getInstance().buildInputBool(t);
        if(!input)
        {
            LOG << F("ERROR: Failed to create input\n");
            return nullptr;
        }

        auto d = new DistanceSensor(*input, *output, constantPoll);
        if(!d->parseMisc(json))
            return nullptr;
        return d;
    }
    //commands
    const char* DistanceSensor::Cmd_Poll = "poll";


    //events
//    const char* DistanceSensor::Event_Active     = "active";
//    const char* DistanceSensor::Event_Inactive   = "inactive";
    const char* DistanceSensor::Event_Changed    = "changed";

    const char* DistanceSensor::Type = "DistanceSensor";
    ObjectConfig<Device> DistanceSensor::DevConf(Type, createFromJson);
}
