#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>
#include "CommandList.h"
CommandList::CommandList(std::vector<std::string> &inputSplit, int &cur,int layer, int &flag){
    bool endPar = false;
    this -> IsConnector = false;
    std::vector<Base*> userCall;
    std::vector<Base*> userInputs;
    std::vector<std::string> passInArg;
    while (cur < inputSplit.size()){
        std::string XcodeTest= inputSplit.at(cur);
        if (inputSplit.at(cur).front() == '('){
            inputSplit.at(cur) = inputSplit.at(cur).substr(1,inputSplit.at(cur).size());
            CommandList* newBase = new CommandList(inputSplit,cur,layer + 1,flag);
            userInputs.push_back(newBase);
            //cur++;
            continue;
        }
        if (inputSplit.at(cur) == "||") {
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                userInputs.push_back(newBase);
            }
            Or *newOr = new Or();
            userInputs.push_back(newOr);
            cur++;
            continue;
        }
        if (inputSplit.at(cur) == "&&"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
            }
            And *newAnd = new And();
            userInputs.push_back(newAnd);
            cur++;
            continue;
        }
        if (inputSplit.at(cur).back() == ';'){
            std::string toPushIn = getColon(inputSplit.at(cur),endPar);
            if (toPushIn.back() == ')'){
                endPar = true;
                toPushIn = toPushIn.substr(0,toPushIn.size()-1);
            }
            std::string test= inputSplit.at(cur);
                if (toPushIn.size() > 0){
                    passInArg.push_back(toPushIn);
                }
            cur++;
            break;
        }
        if (inputSplit.at(cur).back() == ')'){
            endPar = true;
            inputSplit.at(cur) = this -> getPar(inputSplit.at(cur));
        }
        if (!inputSplit.at(cur).empty()){
        passInArg.push_back(inputSplit.at(cur));
        }
        cur++;
        if (endPar){
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
                return ;
            }
            if (j == userInputs.size() -1){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
            if (userInputs.at(j - 1) -> IsConnector){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
            if (userInputs.at(j + 1) -> IsConnector){
                flag = -1;
                userInputs.at(j) ->fetch_name();
                return;
            }
        }
    }
    this -> Actions = (splitBuild(userInputs));
}
CommandList::~CommandList(){
    delete this -> Actions;
}
std::string CommandList:: getColon (std::string input,bool &endPar){
    input = input.substr(0,input.size() -1);
    if (input.back() == ')'){
        endPar = true;
        return getPar(input);
    }
    return input;
}
std::string CommandList::getPar(std::string input){
    input = input.substr(0,input.size() -1);
    if (input.back() == ';'){
            input = input.substr(0,input.size() -1);
            return input;
        }
    return input;
}




Base* CommandList::splitBuild(std::vector<Base*> &userInputs){
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

Base* CommandList::build(Base* left, Base* right){
    if (right -> IsConnector){
        right -> add_left(left);
        return right;
    }
    left ->add_right(right);
        return left;
}
void CommandList::execute(int &flag){
    Actions -> execute(flag);
}
//junk functions
void CommandList::add_left(Base* right){}
void CommandList::add_right(Base* left){}
void CommandList::fetch_name(){}
