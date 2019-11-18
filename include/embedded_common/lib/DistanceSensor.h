// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "DigitalInputPin.h"
#include "DigitalOutputPin.h"

#define CM 28
#define INC 71

namespace omni
{
  class DistanceSensor :  public DigitalInputPin
  {

  private:

    unsigned short tPin; //(pin)
    unsigned short ePin; //(pin)

    DigitalInputPin* echoPin; //(inputPin) echo is the input pin which is read. data types must coorespond
    DigitalOutputPin* trigPin; //(outputPin) trigger is the output pin which is manipulated. data types must coorespond

    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();

    void sendJsonPacket();

  protected:

  public:
    DistanceSensor(unsigned short trigPin, unsigned short echoPin, unsigned long timeOut = 20000UL);

    virtual ~DistanceSensor();

    virtual bool configure();

    virtual unsigned long timing();

    static InputBool* createFromJson(const char* json);

    void setTimeout(unsigned long timeOut) {timeout = timeOut;}
    void setMaxDistance(unsigned long dist) {timeout = dist*CM*2;}


    //Type
    static const char* Type;

    //json commands
    static const char* Cmd_Poll;

    //params
    static const char* Param_Distance;

    //events
    static ObjectConfig<InputBool> InputBoolConf;

  };
}
#endif
