#ifndef MKDIR_H
#define MKDIR_H
#include <string>
#include <vector>
#include "Command.h"
class Mkdir :public Command{
    private:
        void add_right(Base *right);
    public:
        Mkdir(std::vector<std::string> folders);
        void execute();
        void print_error();
};
#endif
