#include <iostream>
#include <vector>
#include "commandLine.h"

commandLine::commandLine(){
    this -> baseOutput = "my computer";
}

void commandi_line::runShell(){
    std::cout << baseOutput << endl;
    std::string userInput;
    std::vector <string> inputs
    while (std::cin >> userInput){
        inputs.push_back(userInput);
    }
