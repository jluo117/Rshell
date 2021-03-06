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


    bool openQ = false;
    int leftP = 0;
    int rightP = 0;
    int leftB = 0;
    int rightB  = 0;

    for (unsigned i = 0; i < UserInput.size(); i++) {
        if (UserInput.at(i) == '"'){
            if (openQ){
                openQ = false;
            }
            else{
                openQ = true;
            }
        }
        else if (UserInput.at(i) == '#'){
            if (!openQ){
                UserInput = UserInput.substr(0, i);
            }
        }

        else if (UserInput.at(i) == '('){
            if(!openQ){
                leftP++;

            }
        }
        else if (UserInput.at(i) == ')'){
            if(!openQ){
                rightP++;
                if (rightP > leftP){
                    std::cout << "Warning: extra right parenthesis found" << std::endl;
                    flag = -1;
                    break;
                }
            }

        }
        else if (UserInput.at(i) == '['){
            if (!openQ){
            leftB++;

            }
        }
        else if (UserInput.at(i) == ']'){
            if(!openQ){
                rightB++;
                if (rightB > leftB){
                    std::cout << "Warning: extra right bracket found" << std::endl;
                    flag = -1;
                    break;
                }
            }
        }
    }
    if (openQ){
        std::cout << "Warning: unbalanced quotation marks" << std::endl;
        continue;
    }
    if (flag == -1){
        continue;
    }
    Tok tok(UserInput, sep);
    for (Tok::iterator it = tok.begin(); it != tok.end(); ++it){
        inputSplit.push_back(*it);
    }

        if ( !openQ && (leftP != rightP) ){
            std::cout << "Warning: unbalanced parenthesis" << std::endl;
            flag = -1;
            continue;
        }
        if ( !openQ && (leftB != rightB) ) {
            std::cout << "Warning: unbalanced brackets" << std::endl;
            flag = -1;

            continue;
        }
        if (flag == -1){
            continue;
        }
    while (cur < inputSplit.size() ){
        CommandList *newBase = new CommandList(inputSplit,cur,2,flag);
        userInputs.push_back(newBase);
        if (flag == -1){
           break;
        }
        //cur++;
    }
    if (flag == -1){
        continue;
    }
    for (unsigned i = 0; i < userInputs.size(); i++){
        int pipes [2];
        int size = 0;
        userInputs.at(i) -> execute(flag,pipes,false,false,size);
    }
    }
}

