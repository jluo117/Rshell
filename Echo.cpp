#include <iostream>
#include <vector>
#include <string>
#include "Echo.h"
Echo::Echo(std::vector<std::string> input){
    this -> Argv = input;
    this -> IsValid = true;
}
void Echo::add_right(Base *right){
}
void Echo::execute(){
    std::cout << this -> Argv.at(0);
    for (int i = 1; i < this ->Argv.size(); i++){
        std::cout << ' ' << this -> Argv.at(i);
    }
    std::cout << std::endl;
}
void Echo::print_error(){
    
}
