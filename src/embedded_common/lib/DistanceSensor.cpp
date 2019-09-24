/*
 * A port of Library for hcsr04 Ranging Module in a minimalist way
 * created 3 Apr 2014 by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 */
 /*
 * For ESP support, we just need to add a new file to src/embedded_common/lib called something like hcsr04.cpp .
 * It would derive from the class called InputFloat and would return the measured distance in its getFloat() method.
 * Elsewhere we could handle the conversion from the float to a boolean based on it being greater than or equal to a range.
 */

#include "DistanceSensor.h"

#include "OmniThing.h"
#include "Logger.h"
#include "OmniUtil.h"
#include <Arduino.h>
#include "frozen.h"
#include <string.h>

namespace omni
{

DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut) {
  trig = trigPin;
  echo = echoPin;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  timeout = timeOut;
}

unsigned int DistanceSensor::timing() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  previousMicros = micros();
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
  previousMicros = micros();
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout

  return micros() - previousMicros; // duration
}

/*
 * If the unit of measure is not passed as a parameter,
 * by default, it will return the distance in centimeters.
 * To change the default, replace CM by INC.
 */
unsigned int DistanceSensor::read(uint8_t und) {
  return timing() / und / 2;  //distance by divisor
}
}
