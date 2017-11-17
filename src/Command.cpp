#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include<fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Command.h"
#include <unistd.h>
Command::Command(std::vector<std::string> userEnter){
    this -> IsConnector = false;
    this -> Left = this;
    this -> Right= this;
    if (userEnter.at(0).back() == ';'){
        userEnter.at(0) = userEnter.at(0).substr(0,userEnter.at(0).size() -1);
    }
    //casting string to char
    for (unsigned i = 0; i < userEnter.size(); i++){
        char *cstr = new char[userEnter.at(i).size() + 1];
        strcpy(cstr, userEnter.at(i).c_str());
        this -> Args[i] = cstr;
        this ->  toBlowUp = userEnter.size();
    }
}
Command::~Command(){
    for (int i = 0; i < this -> toBlowUp; i++){
       delete this -> Args[i];
       this -> Args[i] = NULL;
    }
}

void Command::fetch_name(){
    std::string UserCall = this -> Args[0];
    std::cout << "Parsing error near " + UserCall << std::endl;
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
        char *File;
        if (this -> toBlowUp > 2){
            Flag = this -> Args[1];
            File  =  Args[2];
        }
        else{
           Flag = "-e";
           File = this -> Args[1];
        }
        std::ifstream f(File);
        DIR* dir = opendir(File);
        if (Flag == "-e"){
            if ((f.good()) || (dir)){
                std::cout << "(True)" << std::endl;
                status = 0;
                closedir(dir);
                return;
            }
            else{
                std::cout << "(False)" << std::endl;
                status = -1;
                return;
            }
        }
        if (Flag == "-f"){
            if ((f.good()) && (!dir)){
                std::cout << "(True)" << std::endl;
                status = 0;
                return;
            }
            else{
                std::cout << "(False)" << std::endl;
                status = -1;
                return;
            }
        }
        if (Flag == "-d"){
           if (dir){
               std::cout << "(True)" << std::endl;
               status = 0;
               closedir(dir);
               return;
           }
           else{
               std::cout << "(False)" << std::endl;
               status = -1;
               return;
           }
        }
        std::cout << "Invalid command " << std::endl;
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

