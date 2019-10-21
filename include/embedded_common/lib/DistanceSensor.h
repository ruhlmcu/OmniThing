// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable

#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

//#include "OutputVoid.h"
//#include "OutputBool.h"

#include "Device.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71

namespace omni
{
  class OutputVoid;
  class DistanceSensor :  public Device
  {

  private:

    uint8_t trig;
    uint8_t echo;
    boolean threePins = false;
    unsigned long previousMicros;
    unsigned long timeout;
    bool m_bLastVal;

    void sendJsonPacket();

  protected:
    void writePin(bool b);
//  virtual void writePin(bool b) = 0;

  public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL, bool constantPoll = true);
    virtual ~DistanceSensor();

    virtual void recvJson(const char* cmd, const char* json);
    virtual void run();
    virtual void init();

    virtual const char* getType() const {return Type;}
    unsigned int read(uint8_t und = CM);
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

    static ObjectConfig<OutputVoid> OutputVoidConf;
    static ObjectConfig<OutputBool> OutputBoolConf;

    static ObjectConfig<Device> DevConf;

  };
}
#endif
