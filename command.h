#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
class command{
    protected:
    std::vector<std::string> argv;
    public:
    virtual bool execute() = 0;
};
#endif
