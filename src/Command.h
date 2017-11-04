#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
#include<sys/types.h>
#include "Base.h"
class Command: public Base{
    ~Command();
    void fetchName();
    void add_left(Base*);
    void add_right(Base*);
    char *Args[200];
    int toBlowUp; //check amount of deletes we need
    public:
        Command(std::vector<std::string> userEnter);
        void execute(int &status);
};
#endif
