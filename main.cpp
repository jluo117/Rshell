#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <set>
#include <boost/algorithm/string.hpp>
#include "Echo.h"
using namespace boost;
int main(){
    std::cout << '$';
    std::string userInput;
    std::vector <std::string>argv;
    std::getline(std::cin,userInput);
    split( argv, userInput, is_any_of(" "), token_compress_on );
    to_lower(argv.at(0));
    if ((argv.at(0))== "echo"){
    Echo *test = new Echo(argv);
    test -> execute();
    }
    return 0;
}

