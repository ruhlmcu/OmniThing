#include "DigitalOutputPinTimed.h"

#if defined(OMNI_PLAT_RPI)
    #include "DigitalOutputPinRaspberryPi.h"
#elif !defined(OMNI_NOT_ARDUINO)
    #include "DigitalOutputPinArduinoTimed.h"
#endif

namespace omni
{
//private


//public
    DigitalOutputPinTimed::DigitalOutputPinTimed(unsigned short pin, bool initialValue, bool invertLogic, unsigned long Duration):
        m_nPin(pin),
        m_bValue(initialValue),
        m_bInvertLogic(invertLogic),
        m_nDuration(Duration)
    {

    }

    DigitalOutputPinTimed::~DigitalOutputPinTimed()
    {

    }

    void DigitalOutputPinTimed::writeVoid() //behaves as a toggle
    {
        writeBool(!m_bValue);
    }

    void DigitalOutputPinTimed::writeBool(bool b)
    {
        bool val = isInverted() ? !b : b;
        m_bValue = b;

        writePin(val);
    }

    DigitalOutputPinTimed* DigitalOutputPinTimed::create(unsigned short pin, bool initialValue, bool invertLogic, unsigned long Duration)
    {
    #if defined(OMNI_PLAT_RPI)
        return new DigitalOutputPinRaspberryPi(pin, initialValue, invertLogic);
    #elif !defined(OMNI_NOT_ARDUINO)
        return new DigitalOutputPinTimedArduino(pin, initialValue, invertLogic, Duration);
    #else
        LOG << F("ERROR: DigitalInputPinTimed not supported on this platform\n");
        return nullptr;
    #endif
    }
}
