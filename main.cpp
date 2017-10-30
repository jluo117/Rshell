#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <set>
#include <list>
//#include <boost/algorithm/string.hpp>
#include "Echo.h"
#include "And.h"
#include "Mkdir.h"
#include "Ls.h"
//using namespace boost;
//int main(){
    /*std::vector<Base*> calls; //collect amount of bases needed to execute
    std::cout << '$';
    std::string userInput;
    std::list <std::string>argv;
    std::vector<std::string> toConvert;
    std::getline(std::cin,userInput);
    split( toConvert, userInput, is_any_of(" "), token_compress_on );
    for (int i = 0; i<toConvert.size(); i++){
       argv.push_back(toConvert.at(i));
      }
    while (argv.size() > 0){
        std::string holder = *argv.begin();
        to_lower(holder);
        if (holder == "echo"){
            std::vector <std::string> passIn;
            while (argv.size() > 1 && argv.begin() -> back() != ';'){
                argv.pop_front();
                if (argv.front() == "||" || argv.front() == "&&"){
                    break;
                }
                passIn.push_back(argv.front());
            }
            Echo *test = new Echo(passIn);
            if ((calls.size() > 0) && (calls.back()-> IsComplete == false)){
                calls.back() -> add_right(test);
            }
            else{
                calls.push_back(test);
            }
            if (argv.begin() -> back()== ';'){
                argv.pop_front();
            }
        }
        else if (holder == "&&"){
            argv.pop_front();
            if ((calls.size() == 0) || (argv.size() == 0)){
                std::cout << "Error" << std::endl;
                return 0;
            }
        And *test = new And(calls.back());
        calls.back() = test;
    }

    }
    for (int i = 0; i < calls.size(); i++){
        calls.at(i) -> execute();
    }
    return 0;
}
*/

int main(){
    std::vector<std::string> hello;
    hello.push_back("hello world");
    Echo *Hello = new Echo(hello);
    std::vector<std::string> bye;
    bye.push_back("bye world");
    Echo *Bye = new Echo(bye);
    And *con = new And(Hello);
    std::vector<std::string> makeFile;
    makeFile.push_back("Hanzo");
    Mkdir *test1 = new Mkdir(makeFile);
    con -> add_right(test1);
    con -> execute();
    Ls *test3 = new Ls(makeFile);
    test3 -> execute();
    return 0;
}
