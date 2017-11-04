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
        int flag = 0;
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

	for (unsigned i = 0; i < UserInput.size(); i++){
	    if (UserInput.at(i) == '#') {
		UserInput = UserInput.substr(0, i);
	    }
	}

        Tok tok(UserInput, sep);
        int connectorCount = 0;
        for(Tok::iterator beg = tok.begin(); beg != tok.end(); ++beg){
        //std::cout << *beg << std::endl;


	    if (*beg == "||") {
                if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                passInArg.clear();
                userInputs.push_back(newBase);
                }
                Or *newOr = new Or();
                userInputs.push_back(newOr);
                connectorCount++;
                continue;
            }
            if (*beg == "&&"){
               // printVector(passInArg);
                if (passInArg.size() > 0){
                Command* newBase = new Command(passInArg);
                userInputs.push_back(newBase);
                passInArg.clear();
                }
                And *newAnd = new And();
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
        }
        std::pair<std::vector<Base*> , int> theCommand;
        theCommand = std::make_pair(userInputs,connectorCount);
        connectorCount = 0;
        toBreak.push_back(theCommand);
        userInputs.clear();
        passInArg.clear();
        



        for (int i = 0; i < toBreak.size(); i++){
            if (toBreak.at(i).first.size() == 0){
                continue;
            }
            std::vector<Base*> userVec = toBreak.at(i).first;
            for (int j = 0; j < userVec.size(); j++){
                if (userVec.at(j) -> IsConnector){
                    if (j == 0){
                        flag = -1;
                        userVec.at(j) ->fetchName();
                        break;
                    }
                    if (j == userVec.size() -1){
                        flag = -1;
                        userVec.at(j) ->fetchName();
                        break;
                    }
                    if (userVec.at(j - 1) -> IsConnector){
                        flag = -1;
                        userVec.at(j) ->fetchName();
                        break;
                    }
                    if (userVec.at(j + 1) -> IsConnector){
                            flag = -1;
                            userVec.at(j) ->fetchName();
                            break;
                    }
                }
            }
            if (flag != -1){
                userCall.push_back(splitBuild(userVec,toBreak.at(i).second));
            }
                if  (flag == -1){
                break;
            }

        }
        if (flag == -1){
           continue;
        }
        for (unsigned i = 0; i <userCall.size(); i++){
            flag = 0;
            userCall.at(i) -> execute(flag);

    }
    }
}
void printVector(std::vector<std::string> test){
    for (unsigned i = 0; i < test.size(); i++){
        std::cout << test.at(i) << ' ';
    }
    std::cout << std::endl;
}

Base* Shell::splitBuild(std::vector<Base*> &userInputs,int connectorCount){
    int q = userInputs.size();
    if (q == 1){
        return userInputs.at(0);
    }
    std::vector<Base*> leftSplit;
    for (int i = 0 ; i < q -2; i++){
        leftSplit.push_back(userInputs.at(i));
    }
    
    Base* leftSpliters = splitBuild(leftSplit,connectorCount);
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


