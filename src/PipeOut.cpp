#include "PipeOut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
PipeOut::PipeOut(std::string targetFile){
    this -> targetFile = targetFile;
    this -> IsSpecial = true;
}
PipeOut::~PipeOut(){
    if (this -> Left){
        delete this -> Left;
    }
    if (this -> Right){
        delete this -> Right;
    }
}
void PipeOut::add_left(Base *left){
    this -> Left = left;
}
void PipeOut::add_right(Base *right){
    this -> Right = right;
}
void PipeOut::fetch_name(){
    std::cout << "parsing error near > " << std::endl;
}

void PipeOut::execute(int &status){
    if (!this -> Left){
        std::cout << "missing left arguement" << std::endl;
        status = -1;
        return;
    }
    this -> Left -> execute(status);
    int pid = fork();
    if (pid == -1){
        perror("fork");
        status = -1;
        exit(1);
        return;
    }
    else if (pid == 0){
        status = open(this -> targetFile.c_str(), O_WRONLY|O_TRUNC);
        if(status == -1) {
				status = creat(this -> targetFile.c_str(), S_IRUSR|S_IWUSR);
        }
        if(status == -1) {
            perror("creat");
            exit(1);
        }
        if(close(1)) {
            status = -1;
            perror("close");
            exit(1);
        }
        if(dup(status) == -1) {
            status = -1;
            perror("dup");
            exit(1);
        }
        exit(0);
    }
    else{
        if (wait(&status) == -1){
            status = -1;
            perror("wait");
            return;
        }
    }
}

