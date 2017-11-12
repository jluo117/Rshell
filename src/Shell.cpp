#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>
#include "Shell.h"
using namespace boost;
Shell::Shell(){
}
void Shell::runShell(){
    while(1){
        int flag = 0;
		std::vector<Base*> userCall;
        std::vector< std::vector<Base*>  >toBreak;
        std::vector<Base*> userInputs;
        std::vector<std::string> inputSplit;
        std::cout <<'$';
        std::string UserInput;
        std::getline (std::cin,UserInput);
        std::vector<std::string> passInArg;
        typedef tokenizer<char_separator<char> > Tok;
        char_separator<char> sep(" "); // default constructed
        int cur = 0;
	for (unsigned i = 0; i < UserInput.size(); i++){
	    if (UserInput.at(i) == '#') {
		UserInput = UserInput.substr(0, i);
	    }
	}
    Tok tok(UserInput, sep);
    for (Tok::iterator it = tok.begin(); it != tok.end(); ++it){
        inputSplit.push_back(*it);
    }
    while (cur < inputSplit.size() ){
        CommandList *newBase = new CommandList(inputSplit,cur,0,flag);
        userInputs.push_back(newBase);
        if (flag == -1){
           break;
        }
        cur++;
    }
    for (int i = 0; i < userInputs.size(); i++){
        userInputs.at(i) -> execute(flag);
    }
    }
}



