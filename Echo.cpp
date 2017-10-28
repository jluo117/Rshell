#include <iostream>
#include <vector>
#include <string>
#include "Echo.h"
Echo::Echo(std::vector<std::string> input){
    for (int i = 1; i < input.size(); i++){
        this -> Argv.push_back(input.at(i));
    }
    this -> IsValid = true;
}

void Echo::execute(){
    std::cout << this -> Argv.at(0);
    for (int i = 1; i < this ->Argv.size(); i++){
        std::cout << ' ' << this -> Argv.at(i);
    }
    std::cout << std::endl;
}
