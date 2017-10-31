#include <iostream>
#include <vector>
#include <string>
#include "Command.h"
#include "And.h"
#include "Or.h"
int main(){
    std::vector<std::string> userInput;
    std::vector<std::string> makefiles;
    userInput.push_back("echo");
    userInput.push_back("lol");
    Command *test1 = new Command(userInput);
    makefiles.push_back("mkdir");
    makefiles.push_back("beee");
    Command *test2 = new Command(makefiles);
    And *andTest = new And(test2);
    andTest -> add_right(test1);
    andTest -> execute();
    Or *orTest = new Or(test2);
    orTest -> add_right(test1);
    orTest -> execute();
    return 0;
}
