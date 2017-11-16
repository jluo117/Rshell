#include <iostream>
#include <regex>
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
        int left = 0;
        int right = 0;
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
        unsigned cur = 0;
	for (unsigned i = 0; i < UserInput.size(); i++){
	    if (UserInput.at(i) == '#') {
		UserInput = UserInput.substr(0, i);
	    }
	}
    //std::string tempInput = UserInput.substr(0, UserInput.size() - 1);
        for (unsigned i = 0; i < UserInput.size(); i++){
            if (UserInput.at(i) == '('){
                left++;
            }
            if (UserInput.at(i) == ')'){
                right++;
            }
            if (right > left){
                flag = -1;
            }
        }
    Tok tok(UserInput, sep);
    for (Tok::iterator it = tok.begin(); it != tok.end(); ++it){
        inputSplit.push_back(*it);
    }
        if (left != right){
            std::cout << "Warning: Computer does not know what to do \n preparing to wipe out your hard drive" << std::endl;
            flag= -1;
            continue;
        }
        if (flag == -1){
            continue;
        }
    while (cur < inputSplit.size() ){
        CommandList *newBase = new CommandList(inputSplit,cur,0,flag);
        userInputs.push_back(newBase);
        if (flag == -1){
           break;
        }
        //cur++;
    }
    for (unsigned i = 0; i < userInputs.size(); i++){
        userInputs.at(i) -> execute(flag);
    }
    }
}
void callError(){
    std::cout << "Warning: Computer does not know what to do \n preparing to wipe out your hard drive" << std::endl;
}


