#include "PipeOut.h"
#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
PipeOut::PipeOut(std::string targetFile,bool append){
    this -> fileName = targetFile;
    this -> IsSpecial = true;
    this -> append = append;
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

void PipeOut::execute(int &status,int pipes[],bool In,bool Out, int &size){
    int passInPipe;
    if (Out){
        passInPipe = pipes[1];
    }
    if (!this -> Left){
            std::cout << "missing left arguement" << std::endl;
            status = -1;
            return;
        }
    if (this -> append){
            pipes[1] = open(this -> fileName.c_str(),O_WRONLY| O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        }
    else{
            pipes[1] = open(this -> fileName.c_str(),O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    }
    this -> Left -> execute(status,pipes,In,true,size);
    close(pipes[1]);
    if (Out){
        pipes[1] = passInPipe;
        this -> Left -> execute(status,pipes,In,true,size);
    }
}
void PipeOut::toStack(std::stack <Base*> &stacker){
    stacker.push(this);
    this -> Left -> toStack(stacker);
}

void PipeOut::execute(){
    int data;
    if (this -> append){
        data = open(this -> fileName.c_str(),O_WRONLY| O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    }
    else{
        data = open(this -> fileName.c_str(),O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    }
    this -> inDir = data;
}



