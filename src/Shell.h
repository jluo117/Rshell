#ifndef SHELL_H
#define SHELL_H
#include <vector>
#include <string>
#include "And.h"
#include "Or.h"
#include "Command.h"
class Shell{
    private:
        Base* build(Base*,Base*,int &flag);
        Base* splitBuild(std::vector<Base*> &userInputs,int connectorCount,int &flag);
    public:
        Shell();
        void runShell();
};
#endif
