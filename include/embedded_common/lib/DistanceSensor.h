// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable

#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "OutputVoid.h"
#include "OutputBool.h"

#include "Device.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71

namespace omni
{
  class OutputVoid;
  class OutputBool;
  class DistanceSensor :  public Device
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
//    InputBool& m_rInput;
    bool m_bInvert;
    bool m_bLastVal;
    unsigned int timing();
    void sendJsonPacket();


  protected:
      virtual void writePin(bool b) = 0;

  public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL, bool constantPoll = true);
    virtual ~DistanceSensor();

    virtual void recvJson(const char* cmd, const char* json);
    virtual void run();
    virtual void init();

    virtual const char* getType() const {return Type;}
//    bool isInverted() const {return m_bInvert;}
    unsigned int read(uint8_t und = CM);

    static Device* createFromJson(const char* json);


    void setTimeout(unsigned long timeOut) {timeout = timeOut;}


    virtual bool configure();

    //Type
    static const char* Type;

    //json commands
    static const char* Cmd_Poll;

    //events
    static const char* Event_Active;
    static const char* Event_Inactive;
    static const char* Event_Changed;

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
    DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}

    virtual ~DistanceSensor();

    virtual bool configure();

    static const char* Type;
    static ObjectConfig<OutputVoid> OutputVoidConf;
    static ObjectConfig<OutputBool> OutputBoolConf;

  };*/
}
#endif
