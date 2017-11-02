#include <iostream>
#include <vector>
#include <string>
#include<boost/tokenizer.hpp>
#include "Shell.h"
using namespace boost;
Shell::Shell(){
}
void Shell::runShell(){
    while(1){
        std::vector<Base*> userCall;
        std::vector<std::vector<Base*> > toBreak;
        std::vector<Base*> userInputs;
        std::vector<std::string> inputSplit;
        std::cout <<'$';
        std::string UserInput;
        std::getline (std::cin,UserInput);
        std::vector<std::string> passInArg;
        tokenizer<> tok(UserInput);
        for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
            if (*beg == "||") {
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                Or *newOr = new Or();
                userInputs.push_back(newBase);
                userInputs.push_back(newOr);
                continue;
            }
            if (*beg == "&&"){
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                And *newAnd = new And();
                userInputs.push_back(newBase);
                userInputs.push_back(newAnd);
                continue;
            }
            passInArg.push_back(*beg);
            if (beg -> back() == ';'){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                toBreak.push_back(userInputs);
                userInputs.clear();
                passInArg.clear();
                continue;
            }
        }
        Command* newBase = new Command(passInArg);
        userInputs.push_back(newBase);
        toBreak.push_back(userInputs);
        userInputs.clear();
        passInArg.clear();
        for (int i = 0; i < toBreak.size(); i++){
            userCall.push_back(splitBuild(toBreak.at(i)));
        }
        for (int i = 0; i <userCall.size(); i++){
            userCall.at(i) -> execute();
    }
    }
}
Base* Shell::splitBuild(std::vector<Base*> &userInputs){

        int q = userInputs.size();
        if (q == 1){
            return userInputs.at(0);
        }
        std::vector<Base*> split1;
        std::vector<Base*> split2;
        for (int i = 0; i < q/2; i++){
              split1.push_back(userInputs.at(i));
        }
        for (int i = q/2 + 1; i < q; i++){
            split2.push_back(userInputs.at(i));
        }
        return build(splitBuild(split1),splitBuild(split2));

}

Base* Shell::build(Base* left, Base* right){
    if (left -> right == 0){
        left -> add_right(right);
        return left;
    }
    else {
        right -> add_left(left);
        return right;
    }
}



