#ifndef ECHO_H
#define ECHO_H
#include <vector>
#include <string>
#include <map>
#include "Command.h"
class Echo: protected Command{
    public:
    Echo(std::vector<std::string> input);
    void execute();
};
#endif
