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
    if (this -> Argv.size() == 0){
	int status;
    char *args[2];

    args[0] = "/bin/ls";        // first arg is the full path to the executable
    args[1] = NULL;             // list of args must be NULL terminated

    if ( fork() == 0 )
        execv( args[0], args ); // child: call execv with the path and the args
    else{
        wait( &status );        // parent: wait for the child (not really necessary)
    }
    }
    else{
        for (int i = 0; i < Argv.size(); i++){
            const char *cstr = this ->Argv.at(i).c_str();
            DIR* dir = ::opendir(cstr);
            if (!dir){
                std::cout << "ls: " << this -> Argv.at(i) <<": No such file or directory" <<std::endl;
                throw(-1);
            }
        execvp(((char *)"ls",cstr), 0);
        }
    }
}

void Ls::print_error(){
    std::cout << "ls: " << this -> ErrorCall << ": No such file or directory" << std::endl;
}
void Ls::add_right(Base *right){
}
