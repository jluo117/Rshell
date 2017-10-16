#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "command.h"

command::command(std::list <std::string> &comdData){
    if (comdData.front() == "echo") {
        this -> baseFunction = comdData.front();
        comdData.pop_front()
        std::string curArg;
        if (comdData.front().front() == '"'){
            while (curArg.back() != '"'){
                curArg = comdData.front();
                this -> functionnCalls.push_back(curArg);
                comdData.pop_front();
            }
            return;
        }
        else{
            std::ifstream echoFile(comdData.front())
                if !(echoFile.is_open()){
                    this -> functionCalls.append(comdData.front + "not found");
                }
                else{
                    std::string curArg;
                    while (echoFile >> curArg){
                        this -> functionCalls.push_back(curArg);
                        }
                }
                comdData.pop_front();
                return;
            }
    }
    else{
        cout << "error cmd not found" << endl;
        exit(1)
        }
    }

