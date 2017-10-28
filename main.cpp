#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include "echo.h"
int main(){
    std::cout << '$';
    std::string userInput;
    std::vector <std::string>argv;
    std::getline(std::cin,userInput);
    std::string argument = "";
    for (int i = 0; i < userInput.size(); i++){
        if (userInput.at(i) == ' '){
            argv.push_back(argument);
            argument = "";
            continue;
        }
        argument += userInput.at(i);
    }
    argv.push_back(argument);
    if (argv.at(0)== "echo"){
    echo *test = new echo(argv);
    test -> execute();
    }
    return 0;
}

