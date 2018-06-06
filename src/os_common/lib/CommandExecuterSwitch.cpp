#include "CommandExecuterSwitch.h"

#include "OmniThing.h"
#include "Logger.h"

#include <string.h>
#include "frozen.h"
#include <thread>

#include <stdio.h>
#include <stdlib.h>

namespace omni
{
//private
    void CommandExecuterSwitch::executeCommandOn()
    {
        LOG << F("Executing: ") << m_CommandStrOn << Logger::endl;
        if(!system(nullptr))
        {
            LOG << F("ERROR: This platform does not support the system() function\n");
            return;
        }

        system(m_CommandStrOn);
    }
    
    void CommandExecuterSwitch::executeCommandOff()
    {
        LOG << F("Executing: ") << m_CommandStrOff << Logger::endl;
        if(!system(nullptr))
        {
            LOG << F("ERROR: This platform does not support the system() function\n");
            return;
        }

        system(m_CommandStrOff);
    }
    
//protected
//public
    CommandExecuterSwitch::CommandExecuterSwitch(const char* commandOn, const char* commandOff, bool multithread):
        m_CommandStrOn(commandOn),
        m_CommandStrOff(commandOff),
        m_bMultithreaded(multithread)
    {

    }

    CommandExecuterSwitch::~CommandExecuterSwitch()
    {

    }

    void CommandExecuterSwitch::writeBool(bool b)
    {
        if(b)
        {
            if(m_bMultithreaded)
            {
                std::thread commandRunner(&CommandExecuterSwitch::executeCommandOn, this);
                commandRunner.detach();
            }
            else
            {
                executeCommandOn();
            }
        }
        else
        {
            if(m_bMultithreaded)
            {
                std::thread commandRunner(&CommandExecuterSwitch::executeCommandOff, this);
                commandRunner.detach();
            }
            else
            {
                executeCommandOff();
            }
        }
    }

    OutputVoid* CommandExecuterSwitch::createFromJson(const char* json)
    {
        unsigned int len = strlen(json);
        char* commandOn;
        char* commandOff;
        bool multithread;

        if(json_scanf(json, len, "{commandOn: %Q, commandOff: %Q}", &commandOn, &commandOff) != 2)
        {
            return nullptr;
        }

        if(json_scanf(json, len, "{multithread: %B}", &multithread) != 1)
        {
            multithread = false;
        }

        return new CommandExecuterSwitch(commandOn, commandOff, multithread);
    }

    const char* CommandExecuterSwitch::Type = "CommandExecuterSwitch";
    ObjectConfig<OutputBool> CommandExecuterSwitch::OutputBoolConf(Type, createFromJson);
}

