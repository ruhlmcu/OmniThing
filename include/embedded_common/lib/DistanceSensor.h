/*
 * A port of Library for hcsr04 Ranging Module in a minimalist way
 * created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 */

#ifndef OMNI_DISTANCESENSOR_H
#define OMNI_DISTANCESENSOR_H


#include "CompositePeripheral.h"
#include "ObjectConfig.h"
#include "InputUInt.h"
#include "InputFloat.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71
namespace omni
{
class DistanceSensor : public InputUInt, public InputFloat
{
  private:
    uint8_t trig;
    uint8_t echo;
    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();

  public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}


};
}
#endif // hcsr04_h
