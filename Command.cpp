#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "Command.h"
#include <unistd.h>
Command::Command(std::vector<std::string> userEnter){
    this -> left = this;
    this -> right= this;
    for (int i = 0; i < userEnter.size(); i++){
        char *cstr = new char[userEnter.at(i).size() + 1];
        strcpy(cstr, userEnter.at(i).c_str());
        this -> Args[i] = cstr;
    }
}

bool Command::execute(){
    std::string exitCheck = this -> Args[0];
    if (exitCheck == "exit"){
    exit(0);
    }
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == 0){
    if(execvp(this -> Args[0],this -> Args) == -1){
        perror("exec");
    }
    }
    if (child_pid > 0){
    if ( wait(0) != -1){
    return false;
    }
    else{
        return true;
    }
    }
    return false;
}
void Command::add_left(Base* none){
}
void Command::add_right(Base* none){
}

