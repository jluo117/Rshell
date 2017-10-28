#include <iostream>
#include <vector>
#include <string>
#include "echo.h"
echo::echo(std::vector<std::string> input){
    for (int i = 1; i < input.size(); i++){
        this -> argv.push_back(input.at(i));
    }
}

bool echo::execute(){
    std::cout << this -> argv.at(0);
    for (int i = 1; i < this ->argv.size(); i++){
        std::cout << ' ' << this -> argv.at(i);
    }
    std::cout << std::endl;
    return true;
}
