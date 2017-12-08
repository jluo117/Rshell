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
void ReDirect::execute(int &status,int pipes[],bool In,bool Out,int &size){
    if ((!this -> Left) || (!this -> Right)){
        std::cout << "parsing error near " << "'|'" <<std::endl;
        status = -1;
        return;
    }
    int write[2];
    int read[2];
    pipe(write);
    dup2(size, 0);
    dup2(write[1], 1);
    close(write[0]);
    this -> Left -> execute(status,write,In,true,size);
    close(write[1]);
    dup2(write[1],size);
    pipe(read);
    dup2(read[1], 1);
    close(read[0]);
    this -> Right -> execute(status,read,true,Out,size);
    close(read[1]);
    size = read[0];
}




