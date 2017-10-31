#include <vector>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<dirent.h>
#include<unistd.h>
#include<iostream>
#include "Ls.h"
Ls::Ls(){
    this -> IsValid = true;
}
Ls::Ls(std::vector<std::string> folders){
    for (int i = 0; i < folders.size(); i++){
        const char *cstr = folders.at(i).c_str();
        DIR* dir = ::opendir(cstr);
        if (!dir){
            this -> IsValid = false;
            this -> ErrorCall = folders.at(i);
            return;
        }
        else{
            this -> Argv.push_back(folders.at(i));
        }
    }
    this -> IsValid = true;
}

void Ls::execute(){
    char *args[4];

    args[0] = "/bin/ls";        // first arg is the full path to the executable
    args[1] = "-a";
    args[2] = "Hanzo";    // list of args must be NULL terminated
    args[3] = NULL;
        if (execv(args[0],args) == -1){
            throw (-1);
        }
    }

void Ls::print_error(){
    std::cout << "ls: " << this -> ErrorCall << ": No such file or directory" << std::endl;
}
void Ls::add_right(Base *right){
}
