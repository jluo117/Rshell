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
    this -> storeData = "";
    this -> IsConnector = false;
    this -> Left = this;
    this -> Right= this;
    if (userEnter.at(0).back() == ';'){
        userEnter.at(0) = userEnter.at(0).substr(0,userEnter.at(0).size() -1);
    }
    this -> toBlowUp = 0;
    //casting string to char
    for (unsigned i = 0; i < userEnter.size(); i++){
        char *cstr = new char[userEnter.at(i).size() + 1];
        strcpy(cstr, userEnter.at(i).c_str());
        this -> Args[i] = cstr;
        if ((((userEnter.at(i) == "<") && (userEnter.at(i-1) == "cat")) || (userEnter.at(i) == ">"))  && (userEnter.at(i + 1) != "-p")){
            this -> pipeMode = true;
        }
        if (userEnter.at(i) == "-p"){
            continue;
        }
         this -> Args[i] = cstr;
         this -> toBlowUp++;
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
    if (pipeMode){
        if (pipe()){
            status = 0;
        }
        else{
            status = -1;
        }
        return;
    }
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
        if (this -> test()){
            status = 0;
        }
        else{
            status = -1;
        }
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
bool Command::isDir(char *fileName){
    DIR* dir = opendir(fileName);
    if (dir){
        closedir(dir);
        return true;
    }
    return false;
}
bool Command::isFile(char *fileName){
    std::ifstream f(fileName);
    return f.good();
}

bool Command::test(){
    std::string Flag;
    char *fileName;
    if (this -> toBlowUp > 2){
        Flag = this -> Args[1];
        fileName  =  Args[2];
    }
    else{
        Flag = "-e";
        fileName = this -> Args[1];
    }
    if (Flag == "-e"){
        if ((this -> isDir(fileName)) || this -> isFile(fileName)){
            std::cout << "(True)" << std::endl;
            return true;
        }
        else{
            std::cout << "(False)" << std::endl;
            return false;
        }
    }
    else if (Flag == "-f"){
        if ((this -> isFile(fileName)) && (!this -> isDir(fileName))){
            std::cout << "(True)" << std::endl;
            return true;
        }
        else{
            std::cout << "(False)" << std::endl;
            return false;
        }
    }
    else if (Flag == "-d"){
        if (this -> isDir(fileName)){
            std::cout << "(True)" << std::endl;
            return true;
        }
        else{
            std::cout << "(False)" << std::endl;
            return false;
        }
    }
    else{
        std::cout << "Invalid command " << std::endl;
    }
    return false;
}
bool Command::pipe(){
    for (int i = 0; i < this -> toBlowUp; i++){
        std::string input = this -> Args[i];
        if (input == "<"){
            if(!this -> cat(Args[i+1])){
                return false;
            }
            i++;
        }
    }
    std::cout << this -> storeData << std::endl;
    return true;
}

bool Command::cat(char *fileName){
    if ((this -> isFile(fileName)) && (!this -> isDir(fileName))){
        std::ifstream inFS;
        inFS.open(fileName);
        std::string userInput;
        if (!this -> storeData.empty()){
            this -> storeData += "\n";
        }
        while (getline(inFS,userInput)){
            this -> storeData += userInput + "\n";
        }
        this -> storeData = this -> storeData.substr(0,this -> storeData.size() -1);
        return true;
    }
return false;
}
//connection only function
void Command::add_left(Base* none){
}
void Command::add_right(Base* none){
}

