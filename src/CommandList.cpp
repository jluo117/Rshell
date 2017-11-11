#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>
#include "CommandList.h"
CommandList::CommandList(Tok tok,Tok::iterator cur,int layer, int &flag){
    std::vector<Base*> userCall;
    std::vector<Base*> userInputs;
    std::vector<std::string> inputSplit;
    while (cur != tok.end()){
        if (*cur == "||") {
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                userInputs.push_back(newBase);
            }
            Or *newOr = new Or();
            userInputs.push_back(newOr);
            continue;
        }
        if (*cur == "&&"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
            }
            And *newAnd = new And();
            userInputs.push_back(newAnd);
            continue;
        }
        passInArg.push_back(*cur);
            if (cur -> back() == ';'){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                toBreak.push_back(userInputs);
                userInputs.clear();
                passInArg.clear();
                break;
            }
    }
    if (passInArg.size() == 0){
    }
    else{
        Command* newBase = new Command(passInArg);
        userInputs.push_back(newBase);
    }
    passInArg.clear();
    for (int j = 0; j < userInputs.size(); j++){
        if (userInputs.at(j) -> IsConnector){
            if (j == 0){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
            if (j == userInputs.size() -1){
                flag = -1;
                userInputs.at(j) ->fetchName();
                return;
            }
            if (userVec.at(j - 1) -> IsConnector){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
            if (userVec.at(j + 1) -> IsConnector){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
        }
    }
    this -> Actions = (splitBuild(userInputs));
}
Base* Shell::splitBuild(std::vector<Base*> &userInputs){
    int q = userInputs.size();
    if (q == 1){
        return userInputs.at(0);
    }
    std::vector<Base*> leftSplit;
    for (int i = 0 ; i < q -2; i++){
        leftSplit.push_back(userInputs.at(i));
    }

    Base* leftSpliters = splitBuild(leftSplit);
    Base* rightSpliters = userInputs.at(q-2);
    rightSpliters->add_right(userInputs.at(q-1));
    return build(leftSpliters,rightSpliters);
}

Base* Shell::build(Base* left, Base* right){
    if (right -> IsConnector){
        right -> add_left(left);
        return right;
    }
    left ->add_right(right);
        return left;
}

