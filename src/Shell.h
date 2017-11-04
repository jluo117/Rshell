#ifndef SHELL_H
#define SHELL_H
#include <vector>
#include <string>
#include "And.h"
#include "Or.h"
#include "Command.h"
class Shell{
    private:
        Base* build(Base*,Base*);
        Base* splitBuild(std::vector<Base*> &userInputs,int connectorCount);
    public:
        Shell();
        void runShell();
};
#endif
