#include "DistanceSensor.h"
#include "OmniThing.h"
#include "Logger.h"
#include "OmniUtil.h"
#include "DigitalOutputPinArduino.h"
#include "DigitalInputPinArduino.h"
#include "frozen.h"
#include <Arduino.h>
#include <string.h>



namespace omni
{

//private
void DistanceSensor::sendJsonPacket()
{
    //What is the purpose of sendJsonPacket
    LOG << F("DistanceSensor.cpp - DistanceSensor::sendJsonPacket\n");

    char buffer[256] = "";

    struct json_out out = JSON_OUT_BUF(buffer, sizeof(buffer));

    LOG << F("DistanceSensor.cpp - buffer ") << buffer << Logger::endl;

    json_printf(&out, "{name: \"%s\", type: \"%s\", distance: \"%f\", status: \"%s\"}",
                getName(), getType(), read(), m_bLastVal ? "open" : "closed");

    OmniThing::getInstance().sendJson(buffer);
}

unsigned int DistanceSensor::checkSensor()
  {
    LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor\n");

    outputPin->configure();
    outputPin->writeBool(LOW);
    sleepMicrosBusy(2);
    outputPin->writeBool(HIGH);
    sleepMicrosBusy(10);
    outputPin->writeBool(LOW);

    inputPin->configure();

    previousMicros = getMicros();
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - starting readBool(): ") << inputPin->readBool() << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - !inputPin->readBool() previousMicros: ") << previousMicros << Logger::endl;
    while(!inputPin->readBool() && (getMicros() - previousMicros) <= timeout)
    {
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #1 readBool(): ") << inputPin->readBool() << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #2 (getMicros() - previousMicros): ") << (getMicros - previousMicros) << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #3 timeout: ") << timeout << Logger::endl;
    } // wait for the echo pin HIGH or timeout
    previousMicros = getMicros();
    LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - inputPin->readBool() previousMicros: ") << previousMicros << Logger::endl;

    while(inputPin->readBool() && (getMicros()  - previousMicros) <= timeout) // wait for the echo pin LOW or timeout
    {
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #4 readBool(): ") << inputPin->readBool() << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #5 (getMicros - previousMicros): ") << (getMicros() - previousMicros) << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor - #6 timeout: ") << timeout << Logger::endl;
    } // wait for the echo pin HIGH or timeout

    return getMicros() - previousMicros; // duration

  }
//public

DistanceSensor::DistanceSensor(const char* name, unsigned short echoPin, unsigned short trigPin, unsigned long timeOut, bool pullup):
      Device(false),
      poll_timer(getMillis() - MIN_DS_POLL_MS),
      ePin(echoPin), // input
      tPin(trigPin), // output
      timeout(timeOut),
      internal_pullup(pullup),
      inputPin(DigitalInputPin::create(ePin, false, internal_pullup)),
      outputPin(DigitalOutputPin::create(tPin, true, false))
    {
    LOG << F("DistanceSensor.cpp - DistanceSensor::DistanceSensor\n");
    }

DistanceSensor::~DistanceSensor()
    {
    LOG << F("DistanceSensor.cpp - DistanceSensor::~DistanceSensor\n");
    }

void DistanceSensor::recvJson(const char* cmd, const char* json)
    {
      if(!strcmp(cmd, Cmd_Poll))
      {
          LOG << F("Poll triggered for ") << getType() << F(" ") << getName() << Logger::endl;
          float tmp = read();
          if(tmp > 40)
              emit(Event_Closed);
          else
          {
              emit(Event_Open);
          }
          m_bLastVal = tmp;
          sendJsonPacket();
      }
  }

void DistanceSensor::run()
{
    float tmp = read();
    if(tmp > 40)
        emit(Event_Closed);
    else
    {
        emit(Event_Open);
    }
    sendJsonPacket();
    m_bLastVal = tmp;
}

void DistanceSensor::init()
{
    m_bLastVal = read();
    sendJsonPacket();
}
Device* DistanceSensor::createFromJson(const char* json)
    {
        LOG << F("DistanceSensor.cpp - DistanceSensor::createFromJson\n");

        //general variables
        unsigned long timeout;
        unsigned short echoPin;
        unsigned short trigPin;
        bool pullup = false;
        unsigned int len = strlen(json);
        json_token t;
        char* name;

        if(json_scanf(json, len, "{name: %Q}", &name) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - name not defined")  << json_scanf(json, len, "{name: %hu}", &name)  << Logger::endl;
            return nullptr;
        }

        if(json_scanf(json, len, "{trigPin: %hu}", &trigPin) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - trigPin not defined")  << json_scanf(json, len, "{trigPin: %hu}", &trigPin)  << Logger::endl;
            return nullptr;
        }
        if(json_scanf(json, len, "{timeOut: %lu}", &timeout) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - timeOut not defined")  << json_scanf(json, len, "{timeOut: %lu}", &timeout) << Logger::endl;
            return nullptr;
        }
        if(json_scanf(json, len, "{echoPin: %hu}", &echoPin) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - echoPin not defined ")  << json_scanf(json, len, "{echoPin: %hu}", &echoPin) << Logger::endl;
            return nullptr;
        }

        auto d =  new DistanceSensor(name, trigPin, echoPin, timeout, pullup);
        d->parseMisc(json);
        return d;
}

float DistanceSensor::read(uint8_t und) {
      LOG << F("DistanceSensor.cpp - DistanceSensor::read checkSensor(): ")  << checkSensor() << Logger::endl;
      LOG << F("DistanceSensor.cpp - DistanceSensor::read und: ")  << und << Logger::endl;
      return checkSensor() / und / 2;  //distance by divisor
    }

    //statics

    const char* DistanceSensor::Type = "DistanceSensor";

    const char* DistanceSensor::Cmd_Poll       = "poll";

    const char* DistanceSensor::Event_Open     = "open";
    const char* DistanceSensor::Event_Closed   = "closed";
    const char* DistanceSensor::Event_Changed  = "changed";

    ObjectConfig<Device> DistanceSensor::DevConf(Type, createFromJson);
}
