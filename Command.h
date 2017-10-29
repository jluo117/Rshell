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
        virtual void execute() = 0;
        virtual void print_error() = 0;
};
#endif
