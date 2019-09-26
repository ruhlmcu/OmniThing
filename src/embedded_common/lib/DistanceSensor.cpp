// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#include "distanceSensor.h"

#include <Arduino.h>
#include <string.h>
#include "frozen.h"


namespace omni
{
//start of DigitalxOutputPinArduino
  distanceSensor* distanceSensor::createFromJson(const char* json)
  {
      unsigned int len = strlen(json);

      unsigned short pin;
      bool initial;
      bool invert;

      if(json_scanf(json, len, "{pin: %hu, initial: %B, invert: %B}", &pin, &initial, &invert) != 3)
      {
          return nullptr;
      }

      return new distanceSensor(pin, initial, invert);
  }
  void distanceSensor::writePin(bool b)
  {
      digitalWrite(getPin(), b);
  }
  distanceSensor::distanceSensor(unsigned short pin, bool initialVal, bool invertLogic):
      DigitalOutputPin(pin, initialVal, invertLogic)
  {
      configure();
      writeBool(initialVal);
  }

  distanceSensor::~distanceSensor()
  {

  }

  bool distanceSensor::configure()
  {
      pinMode(getPin(), OUTPUT);
      return true;
  }

  OutputVoid* distanceSensor::createVoidFromJson(const char* json)
  {
      return createFromJson(json);
  }

  OutputBool* distanceSensor::createBoolFromJson(const char* json)
  {
      return createFromJson(json);
  }

  const char* distanceSensor::Type = "distanceSensor";
  ObjectConfig<OutputVoid> distanceSensor::OutputVoidConf(Type, createVoidFromJson);
  ObjectConfig<OutputBool> distanceSensor::OutputBoolConf(Type, createBoolFromJson);
//end of DigitalOutputPinArduino

//start of DigitalxInputPinArduino
bool distanceSensor::readPin()
{
    return digitalRead(getPin());
}

//public
distanceSensor::distanceSensor(unsigned short pin, bool invertLogic, bool pullup):
    DigitalInputPin(pin, invertLogic),
    m_bPullup(pullup)
{
    configure();
}

distanceSensor::~distanceSensor()
{

}

bool distanceSensor::configure()
{
    if(m_bPullup)
        pinMode(getPin(), INPUT_PULLUP);
    else
        pinMode(getPin(), INPUT);
    return true;
}

InputBool* distanceSensor::createFromJson(const char* json)
{
    unsigned int len = strlen(json);

    unsigned short pin;
    bool invert;
    bool pullup;

    if(json_scanf(json, len, "{pin: %hu, invert: %B, pullup: %B}", &pin, &invert, &pullup) != 3)
        return nullptr;

    return new distanceSensor(pin, invert, pullup);
}

const char* distanceSensor::Type = "distanceSensor";
ObjectConfig<InputBool> distanceSensor::InputBoolConf(Type, createFromJson);
//end of DigitalxInputPinArduino

//public from Ultrasonic Library Example

    distanceSensor::distanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut) {
      trig = trigPin;
      echo = echoPin;
      threePins = trig == echo ? true : false;
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
      timeout = timeOut;
    }

    unsigned int distanceSensor::timing() {
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

    /*
     * If the unit of measure is not passed as a parameter,
     * sby default, it will return the distance in centimeters.
     * To change the default, replace CM by INC.
     */
    unsigned int Ultrasonic::read(uint8_t und) {
      return timing() / und / 2;  //distance by divisor
    }
}
