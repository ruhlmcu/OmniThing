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
    //What is the purpose of sendJsonPacket
    LOG << F("DistanceSensor.cpp - DistanceSensor::sendJsonPacket\n");
    char buffer[256] = "";
    struct json_out out = JSON_OUT_BUF(buffer, sizeof(buffer));

    json_printf(&out, "{name: \"%s\", type: \"%s\", distance: \"%f\", status: \"%s\"}",
                getName(), getType(), read(), m_bValue ? "open" : "closed");

    LOG << buffer << Logger::endl;
    LOG << F("DistanceSensor.cpp - sendJsonPacket ") << getType() << F(" ") << getName()<< F(" ") << read()  << Logger::endl;
    OmniThing::getInstance().sendJson(buffer);
}

float DistanceSensor::checkSensor()
  {
    LOG << F("DistanceSensor.cpp - DistanceSensor::checkSensor\n");
/*
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
*/
  }
//public

DistanceSensor::DistanceSensor(const char* name, unsigned short echoPin, unsigned short trigPin, unsigned long timeOut, bool constantPoll, bool pullup):
      Device(constantPoll),
      echoPin(ePin), // ePin is equivelant of pin - echoPin is equivelant of pinNum
      trigPin(tPin), // tPin is equivelant of pin - trigPin is equivelant of pinNum
      timeout(timeOut),
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
    LOG << F("DistanceSensor.cpp - DistanceSensor::recvJson\n");
        if(!strcmp(cmd, Cmd_Poll))
        {
            LOG << F("DistanceSensor.cpp - Poll triggered for ") << getType() << F(" ") << getName() << Logger::endl;
            read();
            sendJsonPacket();
        }
    }

void DistanceSensor::init()
  {
      LOG << F("DistanceSensor.cpp - DistanceSensor::init\n");
      sendJsonPacket();
  }

void DistanceSensor::run()
  {
    LOG << F("DistanceSensor.cpp - DistanceSensor::run\n");
    float tmp = checkSensor();
    sendJsonPacket();
    }
Device* DistanceSensor::createFromJson(const char* json)
    {
        LOG << F("DistanceSensor.cpp - DistanceSensor::createFromJson\n");
        const char* name = parseName(json);
        if(!name)
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - name not defined\n");
            return nullptr;

        //general variables
        unsigned long timeout;
        bool constantpoll;
        unsigned short ePin;
        unsigned short tPin;
        bool invert;
        unsigned int len = strlen(json);
        json_token t;

        //variables for DigitalInputPinArduino - The Echo (input) pin is where the duration of the signal is recieved from the sensor
//        unsigned short echoPin;
        bool pullup = false;

        //variables for DigitalOutputPinArduino - The Trigger (output) pin is where the signal is sent from the sensor
//        unsigned short trigPin;
        bool initial = true;

        if(json_scanf(json, len, "{trigPin: %hu}", &outputPin) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - trigPin not defined")  << json_scanf(json, len, "{trigPin: %hu}", &outputPin)  << Logger::endl;
            return nullptr;
        }
        if(json_scanf(json, len, "{timeOut: %lu}", &timeout) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - timeOut not defined")  << json_scanf(json, len, "{timeOut: %lu}", &timeout) << Logger::endl;
            return nullptr;
        }
        if(json_scanf(json, len, "{constantPoll %B}", &constantpoll) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - createFromJson - constantPoll not defined")  << json_scanf(json, len, "{constantPoll %B}", &constantpoll) << Logger::endl;
            return nullptr;
        }
        if(json_scanf(json, len, "{echoPin: %hu}", &inputPin) != 1)
        {
            LOG << F("ERROR DistanceSensor.cpp - ")  << json_scanf(json, len, "{echoPin: %hu}", &inputPin) << Logger::endl;
            return nullptr;
        }

        return new DistanceSensor(*outputPin, inputPin, timeout, constantpoll);
}
    /*
     * If the unit of measure is not passed as a parameter,
     * by default, it will return the distance in centimeters.
     * To change the default, replace CM by INC.
     */
float DistanceSensor::read(float und) {
      LOG << F("DistanceSensor.cpp - DistanceSensor::read\n");
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
