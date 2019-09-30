#ifndef OMNI_DIGITALOUTPUTPINTIMED_H
#define OMNI_DIGITALOUTPUTPINTIMED_H

//#include "OutputVoid.h"
//#include "OutputBool.h"
#include "TimedOutputBool.h"

namespace omni
{
    class DigitalOutputPinTimed : public TimedOutputBool
    {
        private:
            unsigned short m_nPin;
            bool m_bValue;
            bool m_bInvertLogic;
            unsigned short m_nDuration;

        protected:
            virtual void writePin(bool b) = 0;

        public:
            DigitalOutputPinTimed(unsigned short pin, bool initialValue, bool invertLogic, unsigned short duration);

            virtual ~DigitalOutputPinTimed();

            virtual bool configure() = 0;

            unsigned short getPin() const {return m_nPin;}
            bool isInverted() const {return m_bInvertLogic;}
            bool getValue() const {return m_bValue;}
            unsigned short getDuration() const {return m_nDuration;}

            void writeVoid() final;
            void writeBool(bool b) final;

            static DigitalOutputPinTimed* create(unsigned short pin, bool initialValue, bool invertLogic, unsigned short duration);
    };
}

#endif
