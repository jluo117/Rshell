#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>
#include "Shell.h"
void printVector(std::vector<std::string> test);
using namespace boost;
Shell::Shell(){
}
void Shell::runShell(){
    while(1){
        std::vector<Base*> userCall;
        std::vector<std::pair < std::vector<Base*> , int > >toBreak;
        std::vector<Base*> userInputs;
        std::vector<std::string> inputSplit;
        std::cout <<'$';
        std::string UserInput;
        std::getline (std::cin,UserInput);
        std::vector<std::string> passInArg;
        typedef tokenizer<char_separator<char> > Tok;
        char_separator<char> sep(" "); // default constructed
        Tok tok(UserInput, sep);
        int connectorCount = 0;
        for(Tok::iterator beg = tok.begin(); beg != tok.end(); ++beg){
        //std::cout << *beg << std::endl;
            if (*beg == "||") {
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                Or *newOr = new Or();
                userInputs.push_back(newBase);
                userInputs.push_back(newOr);
                connectorCount++;
                continue;
            }
            if (*beg == "&&"){
               // printVector(passInArg);
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                And *newAnd = new And();
                userInputs.push_back(newBase);
                userInputs.push_back(newAnd);
                connectorCount++;
                continue;
            }
            passInArg.push_back(*beg);
            if (beg -> back() == ';'){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                std::pair<std::vector<Base*> , int> theCommand;
                theCommand = std::make_pair(userInputs,connectorCount);
                connectorCount = 0;
                toBreak.push_back(theCommand);
                userInputs.clear();
                passInArg.clear();
                continue;
            }
        }
        if (passInArg.size() == 0){
        }
        else{
        Command* newBase = new Command(passInArg);
        userInputs.push_back(newBase);
        std::pair<std::vector<Base*> , int> theCommand;
        theCommand = std::make_pair(userInputs,connectorCount);
        connectorCount = 0;
        toBreak.push_back(theCommand);
        userInputs.clear();
        passInArg.clear();
        }
        for (int i = 0; i < toBreak.size(); i++){
            if (toBreak.at(i).first.size() == 0){
                continue;
            }
            else{
            userCall.push_back(splitBuild(toBreak.at(i).first,toBreak.at(i).second));
            }
        }
        for (int i = 0; i <userCall.size(); i++){
            userCall.at(i) -> execute();

    }
    }
}
void printVector(std::vector<std::string> test){
    for (int i = 0; i < test.size(); i++){
        std::cout << test.at(i) << ' ';
    }
    std::cout << std::endl;
}

Base* Shell::splitBuild(std::vector<Base*> &userInputs,int connectorCount){
        //std::cout << userInputs.size() << std::endl;
        //std::cout <<"looping" << std::endl;
        int q = userInputs.size();
        int leftConnector = 0;
        int rightConnector = 0;
        if (q == 1){
            return userInputs.at(0);
        }
        std::vector<Base*> leftSplit;
        std::vector<Base*> rightSplit;
        if (connectorCount % 2 == 0){
             q = (q/2) + 1;
        }
        else{
             q = q/2;
        }

        for (int i = 0; i < q; i++){
              leftSplit.push_back(userInputs.at(i));
              if (userInputs.at(i) -> IsConnector){
                  leftConnector++;
              }
        }
        for (int i = q  ; i < userInputs.size(); i++){
            rightSplit.push_back(userInputs.at(i));
            if (userInputs.at(i) -> IsConnector){
                rightConnector++;
            }
        }
        Base* leftSpliters = splitBuild(leftSplit,leftConnector);
        Base* rightSpliters = splitBuild(rightSplit,rightConnector);

        return build(leftSpliters,rightSpliters);

}

Base* Shell::build(Base* left, Base* right){
    if (left -> right == 0){
        //std::cout << "building right "<< std::endl;
        left -> add_right(right);
        //left -> execute();
        return left;
    }
    else if (right -> left == 0){
        //std::cout << "building left" << std::endl;
        right -> add_left(left);
        //right -> execute();
        return right;
    }
    else if (left -> left == 0){
        return left;
    }
    else if (right -> right == 0){
        return  right;
    }
    std::cout << "parsing error" << std::endl;
    return right;
}



