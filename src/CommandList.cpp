#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <boost/tokenizer.hpp>
#include "CommandList.h"
CommandList::CommandList(std::vector<std::string> &inputSplit, unsigned &cur,int layer, int &flag){
    std::regex quoteReg{"\""};
    bool endPar = false;
    this -> IsConnector = false;
    std::vector<Base*> userCall;
    std::vector<Base*> userInputs;
    std::vector<std::vector<Base*> > toBreak;
    std::vector<std::string> passInArg;
    std::string quotes;
    bool isTest = false;
    bool inQuotes = false;
    while (cur < inputSplit.size()){
        if (flag == -1){
            return;
        }
        std::string recived= inputSplit.at(cur);
        size_t findLoc = recived.find('"');
        if (findLoc != (std::string::npos)){
            if (inQuotes){
                inQuotes = false;
                recived = regex_replace (recived,quoteReg,std::string(""));
                quotes += " " + recived;
                passInArg.push_back(quotes);
                quotes = "";
            }
            else{
                unsigned endLoc;
                unsigned killLoc = findLoc;
                inQuotes = true;
                bool anotherQuote = false;
                for (unsigned i = killLoc + 1; i < recived.size(); i++){
                    if (recived.at(i) == '"'){
                        anotherQuote = true;
                        endLoc = i;
                        break;
                    }
                }
                if (anotherQuote){
                    inQuotes = false;
                    recived = std::regex_replace (recived,quoteReg,std::string(""));
                    recived = std::regex_replace (recived,quoteReg,std::string(""));
                    //passInArg.push_back(recived);
                    inputSplit.at(cur) = inputSplit.at(cur).substr(endLoc + 1,inputSplit.at(cur).size());
                    unsigned cutOff = inputSplit.at(cur).size();
                    recived = recived.substr(0,recived.size() - cutOff);
                    passInArg.push_back(recived);
                    if (cutOff == 0){
                        cur++;
                    }
                    continue;
                }
                recived = regex_replace (recived,quoteReg,std::string(""));
                quotes = recived;
                cur++;
                continue;

            }
        }
        if (inQuotes){
            quotes += " " + recived;
            cur++;
            continue;
        }

        if (inputSplit.at(cur).front() == '['){
            inputSplit.at(cur) = inputSplit.at(cur).substr(1,inputSplit.at(cur).size());
            if (!passInArg.empty()){
                flag = -1;
                std::cout << "Warning: invalid command" << std::endl;
                return;
            }
            passInArg.push_back("test");
            isTest = true;
        }

        if (isTest){
            size_t brackLoc = inputSplit.at(cur).find(']');
            if (brackLoc != std::string::npos){
                std::string leftBreak = inputSplit.at(cur).substr(0,brackLoc);
                inputSplit.at(cur) = inputSplit.at(cur).substr(brackLoc + 1,inputSplit.at(cur).size());
                std::string rightBreak = inputSplit.at(cur);
                if (!leftBreak.empty()){
                    passInArg.push_back(leftBreak);
                }
                if (!rightBreak.empty()){
                    if (rightBreak.front() == ';'|| rightBreak.front() == ')'){
                        continue;
                    }

                else{
                    std::cout << rightBreak << " is invalid command" << std::endl;
                    flag = -1;
                    return;
                }
            }
        }
        }

        if (inputSplit.at(cur).front() == '('){
            inputSplit.at(cur) = inputSplit.at(cur).substr(1,inputSplit.at(cur).size());
            CommandList* newBase = new CommandList(inputSplit,cur,layer + 1,flag);
            if (flag == -1){
                return;
            }
            userInputs.push_back(newBase);

            //cur++;
            continue;
        }
        if (inputSplit.at(cur) == "|"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                userInputs.push_back(newBase);
            }
            ReDirect *newReDirect = new ReDirect;
            userInputs.push_back(newReDirect);
            cur++;
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
        if (inputSplit.at(cur) == "<"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
            }
            PipeIn *startPipe = new PipeIn(inputSplit.at(cur + 1));
            if (!userInputs.empty()){
            startPipe -> add_left(userInputs.back());
            userInputs.back() = startPipe;
            }
            else{
                userInputs.push_back(startPipe);
            }
            cur += 2;
            continue;
        }
        if (inputSplit.at(cur) == ">"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
            }
            PipeOut *endPipe = new PipeOut(inputSplit.at(cur + 1),false);
            cur += 2;
            
            if (!userInputs.empty()){
                endPipe -> add_left(userInputs.back());
                userInputs.back() = endPipe;
            }
            else{
                userInputs.push_back(endPipe);
            }
            continue;
        }
       if (inputSplit.at(cur) == ">>"){
            if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
            }
           
            PipeOut *endPipe = new PipeOut(inputSplit.at(cur + 1),true);
            cur += 2;
            if (!userInputs.empty()){
                endPipe -> add_left(userInputs.back());
                userInputs.back() = endPipe;
            }
            else{
                userInputs.push_back(endPipe);
            }
            continue;
        }

        size_t breakCheck = inputSplit.at(cur).find(';');
        if (breakCheck != std::string::npos){
            std::string toPushIn = inputSplit.at(cur).substr(0,breakCheck);
            inputSplit.at(cur) = inputSplit.at(cur).substr(breakCheck + 1,inputSplit.at(cur).size());
            if (!toPushIn.empty()){
                passInArg.push_back(toPushIn);
            }
            if (inputSplit.at(cur).size() == 0){
                cur++;
            }
            if (!passInArg.empty()){
                Command *newbase = new Command(passInArg);
                userInputs.push_back(newbase);
            }
            if (!userInputs.empty()){
                toBreak.push_back(userInputs);
            }
            userInputs.clear();
            passInArg.clear();
            continue;
        }
        size_t parCheck = inputSplit.at(cur).find(')');
        if (parCheck != std::string::npos){
            endPar = true;
            std::string passInStr = inputSplit.at(cur).substr(0,parCheck);
            inputSplit.at(cur) = inputSplit.at(cur).substr(parCheck + 1,inputSplit.at(cur).size());
            std::string inside = inputSplit.at(cur);
            if (!passInStr.empty()){
                passInArg.push_back(passInStr);
            }
            if (inputSplit.at(cur).size() == 0){
                cur++;
            }
            break;
    }


        std::string checkPoint =inputSplit.at(cur);
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
    if (!userInputs.empty()){
        toBreak.push_back(userInputs);
    }
    passInArg.clear();
    for (unsigned i = 0; i < toBreak.size(); i++){
        std::vector<Base*> input = toBreak.at(i);
        for (unsigned j = 0; j < input.size(); j++){
            if (input.at(j) -> IsConnector){
                if (j == 0){
                    flag = -1;
                    input.at(j) ->fetch_name();
                    return ;
                }
                if (j == input.size() -1){
                    flag = -1;
                    input.at(j) ->fetch_name();
                    return;
                }
                if (input.at(j - 1) -> IsConnector){
                    flag = -1;
                    input.at(j) ->fetch_name();
                    return;
                }
                if (input.at(j + 1) -> IsConnector){
                    flag = -1;
                    input.at(j) ->fetch_name();
                    return;
                }
            }
            else{
                if (j < input.size() -1){
                    if (!input.at(j + 1) -> IsConnector && !input.at(j + 1) -> IsSpecial){
                        input.at(j+ 1) -> fetch_name();
                        flag = -1;
                        return;
                    }
                }
            }
        }
        this -> Actions .push_back(splitBuild(input));
    }
}
CommandList::~CommandList(){
    for (unsigned i =0; i < this -> Actions.size(); i++){
        delete this -> Actions.at(i);
    }
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
    Base* rightSpliters;
    Base* leftSpliters;
    int q = userInputs.size();
    if (q == 1){
        return userInputs.at(0);
    }
    std::vector<Base*> leftSplit;
        for (int i = 0 ; i < q - 2; i++){
            leftSplit.push_back(userInputs.at(i));
    }
    if (!leftSplit.empty()){
        leftSpliters = splitBuild(leftSplit);
    }
    else{
        leftSpliters = userInputs.at(q -1);
    }
    if (userInputs.size() > 1){
    rightSpliters = userInputs.at(q-2);
    }
    else{
        rightSpliters = userInputs.at(q-1);
    }
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
void CommandList::execute(int &flag,int pipes[],bool In,bool Out){
    if (flag == -1){
        return;
    }
    for (unsigned i = 0; i< this -> Actions.size(); i++){
        this -> Actions.at(i) -> execute(flag,pipes,false,false);
    }
}
//junk functions
void CommandList::add_left(Base* right){}
void CommandList::add_right(Base* left){}
void CommandList::fetch_name(){}
