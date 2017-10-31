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
            this -> Argv.push_back(folders.at(i));
        }
    this -> IsValid = true;
}

void Ls::execute(){
    char *args[this -> Argv.size() + 2];

    std::string dir = "/bin/ls";        // first arg is the full path to the executable
    char *cstr = new char[dir.length() + 1];
    strcpy(cstr, dir.c_str());
    args[0] = cstr;
    for (int i = 0; i < this -> Argv.size(); i++){
        char *arg = new char[this -> Argv.at(i).length() + 1];
        strcpy(arg, this -> Argv.at(i).c_str());
        args[i+1] = arg;
    }
    args[this -> Argv.size() + 1] = NULL;
        if (execv(args[0],args) == -1){
            throw (-1);
        }
    }

void Ls::print_error(){
    std::cout << "ls: " << this -> ErrorCall << ": No such file or directory" << std::endl;
}
void Ls::add_right(Base *right){
}
