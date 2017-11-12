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

	for (unsigned i = 0; i < UserInput.size(); i++){
	    if (UserInput.at(i) == '#') {
		UserInput = UserInput.substr(0, i);
	    }
	}
    Tok tok(UserInput, sep);
    Tok::iterator beg = tok.begin();
    while (beg != tok.end()){
        CommandList newBase = new CommandList(tok,beg,0,flag);
        userInputs.push_back(newBase);
    }
    for (int i = 0; i < userInputs.size(); i++){
        userInputs.at(i) -> execute(flag);
    }
    }
}



