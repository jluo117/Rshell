#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
#include<sys/types.h>
#include "Base.h"
class Command: public Base{
    void fetchName();
    void add_left(Base*);
    void add_right(Base*);
    char *Args[99999];
    public:
        Command(std::vector<std::string> userEnter);
        void execute(int &status);
};
#endif
