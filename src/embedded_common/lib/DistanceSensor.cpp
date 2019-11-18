#include "DistanceSensor.h"

#include <Arduino.h>
#include <string.h>
#include "frozen.h"

namespace omni
{
//private

//protected

unsigned long DistanceSensor::timing()
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
//public

    DistanceSensor::DistanceSensor(unsigned short trigPin, unsigned short echoPin, unsigned long timeOut):
      tPin(trigPin), //output pin
      ePin(echoPin), //input pin
      timeout(timeOut),
      echoPin(DigitalInputPin::create(ePin, false, internal_pullup)),
      trigPin(DigitalOutputPin::create(tPin, true, false))

    {

    }

    DistanceSensor::~DistanceSensor()
    {

    }

    bool DistanceSensor::configure()
    {
        if(m_bPullup)
            pinMode(getPin(), INPUT_PULLUP);
        else
            pinMode(getPin(), INPUT);
        return true;
    }
    InputBool* DistanceSensor::createFromJson(const char* json)
    {
        unsigned int len = strlen(json);

        unsigned short echoPin;
        unsigned short trigPin;
        unsigned long timeOut;


        if(json_scanf(json, len, "{trigPin: %B, echoPin: %B, timeOut: %B}", &trigPin, &echoPin,&timeOut) != 3)
        {
            LOG << F("ERROR: inputs required\n");
            return nullptr;
        }

        return new DistanceSensor(trigPin, echoPin, timeOut);
    }

    //commands
    const char* DistanceSensor::Cmd_Poll = "poll";

    //statics
    const char* DistanceSensor::Param_Distance = "distance";

    const char* DistanceSensor::Type = "DistanceSensor";
    ObjectConfig<Device> DistanceSensor::DevConf(Type, createFromJson);
}
