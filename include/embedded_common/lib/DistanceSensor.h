// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "Device.h"


 * Values of divisors

#define CM 28
#define INC 71

namespace omni

  class DistanceSensor :  public Device
  {

  private:

    uint8_t trig;
    uint8_t echo;
    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();

    void sendJsonPacket();

  protected:
    void writePin(bool b);
//  virtual void writePin(bool b) = 0;

  public:
    DistanceSensor(InputUInt& trigPin, InputUInt& echoPin, unsigned long timeOut = 20000UL, bool constantPoll = true);
    virtual ~DistanceSensor();

    virtual void recvJson(const char* cmd, const char* json);
    virtual void run();
    virtual void init();

    virtual const char* getType() const {return Type;}
    unsigned int read(unsigned int und = CM);
    unsigned int timing();

    static Device* createFromJson(const char* json);

    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

    virtual bool configure();

    //Type
    static const char* Type;

    //json commands
    static const char* Cmd_Poll;

    //events

    static const char* Event_Changed;

    static ObjectConfig<InputUInt> InputUIntConf;
    static ObjectConfig<OutputBool> OutputBoolConf;

    static ObjectConfig<Device> DevConf;

  };
}
#endif
