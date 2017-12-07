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
    int tempPipe [2];

    if (pipe(tempPipe) == -1){
            perror("pipe");
            status = -1;
            return;
    }
    int curSize = size;
    this -> Left -> execute(status,tempPipe,false,true,size);

    close(tempPipe[1]);
    if (status == -1){
        return;
    }
    if (Out){
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        size += 2;
        pipes[1] = tempPipe[0];
        this -> Right -> execute(status,pipes,true,true,size);
        int newPipe[20];
        for (int i = 0; i < curSize; i++){
            newPipe[i] = pipes[i];
        }
        for (int i = curSize; i < size; i++){
            newPipe[i] = tempPipe[i];
        }
    }
    else{
        this -> Right -> execute(status,tempPipe,true,Out,size);
    }
    close(tempPipe[0]);
    if (status == -1){
        return;
    }
}




