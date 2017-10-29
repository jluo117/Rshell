#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "Mkdir.h"
Mkdir::Mkdir(std::vector<std::string> folders){
    for (int i = 0; i < folders.size(); i++){
        const char *cstr = folders.at(i).c_str();
        DIR* dir = ::opendir(cstr);
        if (dir)
        {
            /* Directory exists. */
            this -> IsValid = false;
            this -> ErrorCall = folders.at(i);
        }
        this -> Argv.push_back(folders.at(i));
        }
      this -> IsValid = true;
}
void Mkdir::execute(){
    for (int i = 0; i < Argv.size(); i++){
        std::string currentDir = Argv.at(i);
        const char *cstr = currentDir.c_str();
        int stat = ::mkdir(cstr, 0777);
        if (stat == -1){
            std::cout << "mkdir: " << currentDir << " already exisits" << std::endl;
        }
    }
}
void Mkdir::print_error(){
     std::cout << "mkdir: " << this -> ErrorCall << " already exisits" << std::endl;
}
void Mkdir::add_right(Base *right){
}

