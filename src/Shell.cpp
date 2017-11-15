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
        std::regex e ("\\b(\")([^ ]*)");
        std::regex p1 ("\\b(()([^ ]*)");
        std::regex p2 ("\\b())([^ ]*)")
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
    UserInput = std::regex_replace (UserInput, p1, "( ");
    UserInput = std::regex_replace (UserInput, p2, " )"); 
    Tok tok(UserInput, sep);
    for (Tok::iterator it = tok.begin(); it != tok.end(); ++it){
        if ((it -> back() == ')') || ((it -> back() == ';') && (it -> at(it -> size() -2) == ')'))){
            right++;
        }
            if (right > left){
                std::cout << "Warning: Computer does not know what to do \n preparing to wipe out your hard drive" << std::endl;
                flag = -1;
                break;
            }
        else if (it -> front() == '(' ){
            left++;
        }
        if (it -> front() == '"'){
            std::string newString = it -> substr(1,it -> size()-1);
            it++;
            while (it != tok.end()){
                if (it -> find('"')!= std::string::npos){
                    std::string holder = std::regex_replace (*it,e,"");
                    newString += " " + holder;
                    *it++;
                    break;
                }
                newString += " " + *it;
                *it++;
            }
            if (newString.back() == '"'){
                newString = newString.substr(0,newString.size() -1);
            }
            newString = std::regex_replace (newString,e,"$2");
            inputSplit.push_back(newString);
            break;
        }
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


