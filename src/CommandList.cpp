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
    std::vector<std::string> passInArg;
    std::string quotes;
    bool isTest = false;
    bool inQuotes = false;
    while (cur < inputSplit.size()){
        std::string recived= inputSplit.at(cur);
        size_t findLoc = recived.find('"');
        if (findLoc != (std::string::npos)){
            if (inQuotes){
                inQuotes = false;
                recived = regex_replace (recived,quoteReg,"");
                quotes += " " + recived;
                passInArg.push_back(quotes);
                quotes = "";
            }
            else{
                unsigned killLoc = findLoc;
                inQuotes = true;
                bool anotherQuote = false;
                for (size_t i = killLoc; i < recived.size(); i++){
                    if (recived.at(i) == '"'){
                        anotherQuote = true;
                    }
                }
                if (anotherQuote){
                    inQuotes = false;
                    recived = std::regex_replace (recived,quoteReg,"");
                    recived = std::regex_replace (recived,quoteReg,"");
                    passInArg.push_back(recived);
                    cur++;
                    continue;
                }
                recived = regex_replace (recived,quoteReg,"$2");
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
                std::cout << "Your command is invalid.\n go play some World of Warcraft" << std::endl;
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
            break;
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
    passInArg.clear();
    for (unsigned j = 0; j < userInputs.size(); j++){
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
    if (flag == -1){
        return;
    }
    Actions -> execute(flag);
}
//junk functions
void CommandList::add_left(Base* right){}
void CommandList::add_right(Base* left){}
void CommandList::fetch_name(){}
