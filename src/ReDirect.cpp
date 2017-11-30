#include "ReDirect.h"
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <fcntl.h>
ReDirect::ReDirect(){
    this -> IsConnector = true;
    this -> Left = 0;
    this -> Right = 0;
}
ReDirect::~ReDirect(){
    delete this -> Right;
    delete this -> Left;
}
void ReDirect::fetch_name(){
    std::cout << "parsing error near " << "'|'" << std::endl;
}
void ReDirect::add_right(Base *right){
    this -> Right = right;
}
void ReDirect::add_left(Base *left){
    this -> Left = left;
}
void ReDirect::execute(int &status,bool In,bool Out){
    if ((!this -> Left) || (!this -> Right)){
        std::cout << "parsing error near " << "'|'" <<std::endl;
        status = -1;
        return;
    }
    this -> Left -> execute(status,true,true);
    int pid = fork();
    if (pid == -1){
        perror("fork");
        status = -1;
        exit(1);
    }
    else if (pid == 0){
        if(pipe(&status) == -1) {
            perror("pipe");
            exit(1);
        }
        if(dup(status) == -1) {
            status = -1;
            perror("dup1");
            exit(1);
        }
        if(close(status) == -1) {
            status = -1;
            perror("close");
            exit(1);
        }
        this -> Right -> execute(status,In,Out);
        exit(0);
    }
    else{
        if (wait(&status) == -1){
            status = -1;
            perror("wait");
            exit(1);
        }
    }
}




