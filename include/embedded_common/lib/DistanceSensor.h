// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable

#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "OutputVoid.h"
#include "OutputBool.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71

namespace omni
{
  class distanceSensor : public OutputVoid, public OutputBool
  {

  private:
    unsigned short m_nPin;
    bool m_bValue;
    bool m_bInvertLogic;
    uint8_t trig;
uint8_t echo;
boolean threePins = false;
unsigned long previousMicros;
unsigned long timeout;
unsigned int timing();

  protected:
      virtual void writePin(bool b) = 0;

  public:
    distanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

    virtual ~triggerPin();

    virtual bool configure();

    static const char* Type;
    static ObjectConfig<OutputVoid> OutputVoidConf;
    static ObjectConfig<OutputBool> OutputBoolConf;

  };
/*  class triggerPin : public OutputVoid, public OutputBool, public OutputFloat
  {

  private:
      static triggerPin* createFromJson(const char* json);
      static

  protected:
      void writePin(bool b) = 0;

  public:
    distanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

    virtual ~distanceSensor();

    virtual bool configure();

    static const char* Type;
    static ObjectConfig<OutputVoid> OutputVoidConf;
    static ObjectConfig<OutputBool> OutputBoolConf;

  };*/
}
#endif
