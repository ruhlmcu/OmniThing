// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "CompositePeripheral.h"
#include "ObjectConfig.h"
#include "DigitalInputPin.h"
#include "DigitalOutputPin.h"

#include "Device.h"


// Values of divisors

#define CM 28
#define INC 71

namespace omni
{
// Do i need a class statement here for Input or Output classes?
// class InputUInt; // possible inputs are InputFloat, InputBool, InputUInt
// class OutputFloat; // possible outputs are OutputBool, OutputFloat, OutputString, OutputVoid

  class DistanceSensor :  public Device
  {

  private:
    unsigned short tPin; //(pin)
    unsigned short ePin; //(pin)
    bool internal_pullup;

    DigitalInputPin* echoPin; //(inputPin) echo is the input pin which is read. data types must coorespond
    DigitalOutputPin* trigPin; //(outputPin) trigger is the output pin which is manipulated. data types must coorespond

    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();

    void sendJsonPacket();

  protected:
  public:
    DistanceSensor(unsigned short trigPin, unsigned short echoPin, unsigned long timeOut = 20000UL, bool constantPoll = true);
    virtual ~DistanceSensor();

    virtual void recvJson(const char* cmd, const char* json);

    virtual const char* getType() const {return Type;}

    virtual unsigned int read(unsigned int und = CM); // adding virtual mimics MotionSensor not found in Ultrasonic

    static Device* createFromJson(const char* json);

    void setTimeout(unsigned long timeOut) {timeout = timeOut;}
    void setMaxDistance(unsigned long dist) {timeout = dist*CM*2;}


    //Type
    static const char* Type;

    //json commands
    static const char* Cmd_Poll;

    //params
    static const char* Param_Distance;

    //events

    static ObjectConfig<Device> DevConf;

  };
}
#endif
