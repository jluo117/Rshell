#ifndef LS_H
#define LS_H
#include <vector>
#include <string>
#include "Command.h"
class Ls:public Command{
    private:
        void add_right(Base *right);
    public:
        Ls();
        Ls(std::vector<std::string> folders);
        void execute();
        void print_error();
};
#endif
