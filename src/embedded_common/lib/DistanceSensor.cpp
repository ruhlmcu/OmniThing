// A port of Rob Tillaart's Arduino DHT library to OmniThing
// https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
#include "DistanceSensor.h"

#include <Arduino.h>
#include <string.h>
#include "frozen.h"


namespace omni
{


//public from Ultrasonic Library Example
    DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut) :
    trig(trigPin),
    echo(echoPin),
    timeout(timeOut)
      {
      LOG << F("Made it here #1\n");
      threePins = trig == echo ? true : false;
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
      }
    unsigned int DistanceSensor::timing() {
      LOG << F("Made it here #2\n");
      if (threePins)
        pinMode(trig, OUTPUT);

      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      if (threePins)
        pinMode(trig, INPUT);

      previousMicros = micros();
      while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
      previousMicros = micros();
      while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout

      return micros() - previousMicros; // duration
    }

    /*
     * If the unit of measure is not passed as a parameter,
     * sby default, it will return the distance in centimeters.
     * To change the default, replace CM by INC.
     */
    unsigned int DistanceSensor::read(uint8_t und) {
      LOG << F("Made it here #3\n");
      return timing() / und / 2;  //distance by divisor
    }
}
