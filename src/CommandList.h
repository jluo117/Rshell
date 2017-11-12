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
    public:
        CommandList(Tok tok,Tok::iterator cur,int layer);
        ~CommandList();
        void execute(int &flag);
};
