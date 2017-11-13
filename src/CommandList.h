#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include <boost/tokenizer.hpp>
#include "Command.h"
#include "Or.h"
#include "And.h"
using namespace boost;
class CommandList: public Base{
    private:
        Base* build(Base*, Base*);
        Base* splitBuild(std::vector<Base*> &userInputs);
        Base* Actions;
        std::string getColon (std::string input,bool &endPar);
        std::string getPar (std::string input);
    public:
        CommandList(std::vector<std::string>& inputSplit, int &cur,int layer, int &flag);
        ~CommandList();
        void execute(int &flag);
        void add_left(Base*);
        void add_right(Base*);
        void fetch_name ();
};
#endif

