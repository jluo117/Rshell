#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <map>
#include <stack>
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
        void toStack(std::stack <Base*> &stacker);
        Command(std::vector<std::string> userEnter);
        void execute(int &status,int pipes[],bool In,bool Out, int &size);
        void execute();
    private:
        bool isDir(char *fileName);
        bool isFile(char *fileName);
        bool test();
};
#endif
