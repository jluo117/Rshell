#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "echo.h"
using namespace boost;
int main(){
    std::cout << '$';
    std::string userInput;
    std::vector <std::string>argv;
    std::getline(std::cin,userInput);
    split( argv, userInput, is_any_of(" "), token_compress_on );
    if (argv.at(0)== "echo"){
    echo *test = new echo(argv);
    test -> execute();
    }
    return 0;
}

