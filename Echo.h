#ifndef ECHO_H
#define ECHO_H
#include <vector>
#include <string>
#include <map>
#include "Command.h"
class Echo: public Command{
    public:
    Echo(std::vector<std::string> input);
    void add_right(Base *right);
    void execute();
    void print_error();
};
#endif
