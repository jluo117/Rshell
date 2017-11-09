#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
    if (userEnter.at(0).back() == ';'){
        userEnter.at(0) = userEnter.at(0).substr(0,userEnter.at(0).size() -1);
    }
    //casting string to char
    for (unsigned i = 0; i < userEnter.size(); i++){
        char *cstr = new char[userEnter.at(i).size() + 1];
        strcpy(cstr, userEnter.at(i).c_str());
        this -> Args[i] = cstr;
        this -> toBlowUp++;
    }
}
Command::~Command(){
    for (int i = 0; i < toBlowUp; i++){
       delete this -> Args[i];
    }
}
//connector only function
void Command::fetchName(){
}
void Command::execute(int &status){

    std::string CommandCheck = this -> Args[0];
    if (CommandCheck == "exit"){
    while(1){
        exit(0);
    }
    }
    if (CommandCheck == ";"){
        return;
    }
    else if (CommandCheck == "test"){
        std::string Flag;
        std::string File;
        if (this -> toBlowUp > 2){
            flag = this -> Args[1];
            File = this -> Args[2];
        }
        else{
           flag = "-e";
           File = this -> Args[1];
        }

        if (flag == "-e"){
            std::ifstream f(File);
            if (f.good()){
                status = 0;
                return;
            }
            DIR* dir = opendir(File);
            else if (dir){
                status = 0;
                return;
            }
            else{
                status = -1;
                return;
            }
        }
        if (flag == "-f"){
            std::ifstream f(File);
            if (f.good()){
                status = 0;
                return;
            }
            else{
                status = -1;
            }
        }
        if (flag == "-d"){
           DIR* dir = opendir(File);
           if (dir){
               status = 0;
               return;
           }
           else{
               status = -1;
               return;
           }
        }
        status = -1;
        return;
    }

    int pid = fork();
	//child fuction is running
    if (pid == 0){
		status=execvp(this-> Args[0],this -> Args);
        perror("execvp");
        exit(status);
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
//connection only function
void Command::add_left(Base* none){
}
void Command::add_right(Base* none){
}

