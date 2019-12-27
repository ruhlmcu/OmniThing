#ifndef OMNI_OMNIUTIL_H
#define OMNI_OMNIUTIL_H
#define LED_RED 14
#define LED_GREEN 12

namespace omni
{
    unsigned long long getMillis();
    void sleepMillis(unsigned long long ms);
    void sleepMillisBusy(unsigned long long ms);

    unsigned long long getMicros();
    void sleepMicros(unsigned long long us);
    void sleepMicrosBusy(unsigned long long us);

    bool inRange(unsigned lowEnd, unsigned highEnd, unsigned checkVal);

    void flashBuiltIn();
    void flashRed();
    void flashGreen();
}


#endif
