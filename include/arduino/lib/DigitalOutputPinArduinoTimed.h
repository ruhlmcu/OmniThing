#ifndef OMNI_DIGITALOUTPUTPINARDUINOTIMED_H
#define OMNI_DIGITALOUTPUTPINARDUINOTIMED_H

#include "DigitalOutputPinTimed.h"

namespace omni
{
    class DigitalOutputPinArduinoTimed : public DigitalOutputPinTimed
    {
        private:
            static DigitalOutputPinArduinoTimed* createFromJson(const char* json);

        protected:
            void writePin(bool b) final;

        public:
            DigitalOutputPinArduinoTimed(unsigned short pin, bool initialVal, bool invertLogic, unsigned short duration);

            virtual ~DigitalOutputPinArduinoTimed();

            virtual bool configure();

            static OutputVoid* createVoidFromJson(const char* json);
            static OutputBool* createBoolFromJson(const char* json);

            static const char* Type;
            static ObjectConfig<OutputVoid> OutputVoidConf;
            static ObjectConfig<OutputBool> OutputBoolConf;
    };
}
#endif
