#include <iostream>
#include <vector>
#include <string>
#include "Echo.h"
Echo::Echo(std::vector<std::string> input){
    this -> Argv = input;
}
void Echo::add_right(Base *right){
}
bool Echo::execute(){
    std::cout << this -> Argv.at(0);
    for (int i = 1; i < this ->Argv.size(); i++){
        std::cout << ' ' << this -> Argv.at(i);
    }
    std::cout << std::endl;
    return true;
}
