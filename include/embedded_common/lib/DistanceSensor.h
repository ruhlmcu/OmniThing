#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "Device.h"
#include "ObjectConfig.h"
#include "DigitalInputPin.h"
#include "DigitalOutputPin.h"
#define CM 28
#define INC 71

namespace omni
{
  //class OutputBool;
  //class InputBool;

  class DistanceSensor :  public Device
  {

  private:
    unsigned long previousMicros;
    unsigned long timeout;
    bool constantpoll;
    bool m_bValue;
    unsigned short ePin;
    unsigned short tPin;
    bool internal_pullup;
    DigitalInputPin* inputPin;
    DigitalOutputPin* outputPin;

    float checkSensor();
    void sendJsonPacket(); //standard across all devices

  protected:
    static const char* parseName(const char* json);

  public:
    DistanceSensor(const char* name, unsigned short echoPin, unsigned short trigPin, unsigned long timeOut, bool constantPoll, bool pullup);
    virtual ~DistanceSensor();

    virtual void recvJson(const char* cmd, const char* json); //standard across all devices
    virtual void init(); //standard across all devices
    virtual void run(); //standard across all devices

    virtual const char* getType() const {return Type;} //standard across all devices

    virtual float read(float und = CM);
    virtual void setTimeout(unsigned long timeOut) {timeout = timeOut;}
    virtual void setMaxDistance(unsigned long dist) {timeout = dist*INC*2;}

    static Device* createFromJson(const char* json);

    //Type
    static const char* Type;

    //json commands
    static const char* Cmd_Poll;

    //events
    static const char* Event_Open;
    static const char* Event_Closed;
    static const char* Event_Changed;

    static ObjectConfig<Device> DevConf;

  };
}
#endif
