// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable

#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H

#include "DigitalInputPin.h"
#include "DigitalOutputPin.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71

namespace omni
{
    class distanceSensor : public DigitalOutputPin, public DigitalInputPin
    {
        private:

//          private: from Ultrasonic Library Example
            uint8_t trig;
            uint8_t echo;
            bool threePins = false;
            unsigned long previousMicros;
            unsigned long timeout;
            unsigned int timing();

        public:

//          public: from Ultrasonic Library Example
            distanceSensor(uint8_t sigPin) : distanceSensor(sigPin, sigPin) {};
            distanceSensor(uint8_t triggerPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
            unsigned int read(uint8_t und = CM);
            void setTimeout(unsigned long timeOut) {timeout = timeOut;}
    };
}
#endif
