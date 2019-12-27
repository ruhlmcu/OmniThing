#include "OmniUtil.h"
#include <Arduino.h>

namespace omni
{
    unsigned long long getMillis()
    {
        return millis();
    }

    void sleepMillis(unsigned long long ms)
    {
        delay(ms);
    }

    void sleepMillisBusy(unsigned long long ms)
    {
        delay(ms);
    }

    unsigned long long getMicros()
    {
        return micros();
    }

    void sleepMicros(unsigned long long us)
    {
        delayMicroseconds(us);
    }

    void sleepMicrosBusy(unsigned long long us)
    {
        delayMicroseconds(us);
    }
    // Returns true if x is in range [low..high], else false
    bool inRange(unsigned lowEnd, unsigned highEnd, unsigned checkVal)
    {
    return (lowEnd <= checkVal && checkVal <= highEnd);
    }
    void flashBuiltIn()
    {
      pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
      digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);                      // Wait for two seconds
      digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);
    }
    void flashRed()
    {

      pinMode(LED_RED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
      digitalWrite(LED_RED, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_RED, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);                      // Wait for two seconds
      digitalWrite(LED_RED, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_RED, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);
    }
    void flashGreen()
    {
      pinMode(LED_GREEN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
      digitalWrite(LED_GREEN, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_GREEN, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);                      // Wait for two seconds
      digitalWrite(LED_GREEN, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_GREEN, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);
    }
}
