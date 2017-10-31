#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
#include<sys/types.h>
#include "Base.h"
class Command: public Base{
    protected:
        std::string ErrorCall;
        std::vector<std::string> Argv;
    public:
        virtual bool execute() = 0;
};
#endif
