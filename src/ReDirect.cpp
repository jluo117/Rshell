#include "ReDirect.h"
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stack>
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
    int newPipe[2];
    int fd_in = 0;
    std::stack <Base*> master;
    this -> Right -> toStack(master);
    this -> Left -> toStack(master);
    pid_t pid;
    while (!master.empty()){
        pipe(newPipe);
        if ((pid = fork()) == -1){
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one
          if (master.size() > 1)
            dup2(newPipe[1], 1);
          close(newPipe[0]);
          master.top() -> backPipe[0] = newPipe[0];
          master.top() -> backPipe[1] = newPipe[1];
          master.top() -> execute();
          exit(EXIT_FAILURE);
        }
        else{
          wait(NULL);
          close(newPipe[1]);
          fd_in = newPipe[0]; //save the input for the next command
          master.pop();
        }
    }
}

void ReDirect::toStack(std::stack <Base*> &stacker){
    this -> Right -> toStack(stacker);
    this -> Left -> toStack(stacker);
}

void ReDirect::execute(){
//🙄
}



