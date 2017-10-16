#ifndef
#define
#include <iostream>
#include <vector>
#include "command.h"
class commandLine{
    private:
       std::string baseOutput;
       std::vector<command> functionCalls;
    public:
       commandLine();
       void run_shell();
}
#endif
