#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Command.h"
#include <unistd.h>
Command::Command(std::vector<std::string> userEnter){
    this -> IsConnector = false;
    this -> left = this;
    this -> right= this;
    for (unsigned i = 0; i < userEnter.size(); i++){
        char *cstr = new char[userEnter.at(i).size() + 1];
        strcpy(cstr, userEnter.at(i).c_str());
        this -> Args[i] = cstr;
    }
}

void Command::fetchName(){
}
void Command::execute(int &status){

    std::string exitCheck = this -> Args[0];
    if (exitCheck == "exit"){
    exit(0);
    }
    if (exitCheck == ";"){
        return;
    }
    int pid = fork();
	//child fuction is running
    if (pid == 0){
		status=execvp(this-> Args[0],this -> Args);
        perror("execvp");
    }
	else if(pid==-1){
		perror("execvp");
		exit(status);
	}else{
		if(wait(&status) == -1){
		perror("wait");
        }
    }
}
void Command::add_left(Base* none){
}
void Command::add_right(Base* none){
}

