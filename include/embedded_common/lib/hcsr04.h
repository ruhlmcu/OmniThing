/*
 * A port of Library for hcsr04 Ranging Module in a minimalist way
 * created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 */

#ifndef OMNI_HCSR04_H
#define OMNI_HCSR04_H

#include "ObjectConfig.h"
#include "DigitalInputPin.h"
#include "DigitalOutputPin.h"

/*
 * Values of divisors
 */
#define CM 28
#define INC 71
//namespace omni
//{
class hcsr04 {

  private:
    uint8_t trig;
    uint8_t echo;
    unsigned long previousMicros;
    unsigned long timeout;
    unsigned int timing();

  public:
    hcsr04(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut = 20000UL);
    unsigned int read(uint8_t und = CM);
    void setTimeout(unsigned long timeOut) {timeout = timeOut;}


};
//}
#endif // hcsr04_h
