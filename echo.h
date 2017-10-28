#ifndef ECHO_H
#define ECHO_H
#include <vector>
#include <string>
#include <map>
#include "command.h"
class echo: protected command{
    public:
    echo(std::vector<std::string> input);
    bool execute();
};
#endif
