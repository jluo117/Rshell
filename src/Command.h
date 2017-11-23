#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
#include<sys/types.h>
#include "Base.h"
class Command: public Base{
    ~Command();
    void fetch_name();
    void add_left(Base*);
    void add_right(Base*);
    char *Args[200];
    int toBlowUp; //check amount of deletes we need
    std::string storeData;
    public:
        Command(std::vector<std::string> userEnter);
        void execute(int &status);
    private:
        bool isDir(char *fileName);
        bool isFile(char *fileName);
        bool test();
};
#endif
