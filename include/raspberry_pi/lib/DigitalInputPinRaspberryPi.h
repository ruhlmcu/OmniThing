#ifndef OMNI_DIGITALINPUTPINRASPBERRYPI_H
#define OMNI_DIGITALINPUTPINRASPBERRYPI_H

#include "DigitalInputPin.h"

namespace omni
{
    class DigitalInputPinRaspberryPi : public DigitalInputPin
    {
        private:

        protected:
            bool readPin() final;

        public:
            enum class PinMode {Normal, Pullup, Pulldown};

            DigitalInputPinRaspberryPi(unsigned short pin, bool invertLogic, PinMode pm);

            virtual ~DigitalInputPinRaspberryPi();

    };
}

#endif