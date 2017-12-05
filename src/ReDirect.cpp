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
void ReDirect::execute(int &status,int pipes[],bool In,bool Out){
    if ((!this -> Left) || (!this -> Right)){
        std::cout << "parsing error near " << "'|'" <<std::endl;
        status = -1;
        return;
    }
    if (pipe(pipes) == -1){
        perror("pipe");
        status = -1;
        return;
    }
    this -> Left -> execute(status,pipes,false,true);
     close(pipes[1]);

    if (status == -1){
        return;
    }
    this -> Right -> execute(status,pipes,true,Out);
    close(pipes[0]);
    if (status == -1){
        return;
    }
}




