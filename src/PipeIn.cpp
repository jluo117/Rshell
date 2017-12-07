#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "PipeIn.h"
PipeIn::PipeIn(std::string filename){
    this -> Double = true;
    this -> IsSpecial = true;
    this -> fileName = filename;
}
PipeIn::~PipeIn(){
    if (this -> Left){
        delete this -> Left;
    }
    if (this -> Right) {
        delete this -> Right;
    }
}
void PipeIn::add_left(Base *left){
    this -> Left = left;
}
void PipeIn::add_right(Base *right){
    this -> Right = right;
}
void PipeIn::fetch_name(){
    std::cout << "parsing error near < " << std::endl;
}
void PipeIn::execute(int &status,int pipes[],bool In, bool Out, int &size){
    if (size == 0){
        size = 2;
    }
    if (!this -> Left){
        std::cout << "missing left params" << std::endl;
        status = -1;
        return;
    }
    if (this -> Left -> Double){
        this -> Left -> execute(status,pipes,In,Out,size);
    }
    else{
        int pid = fork();

        if(pid == -1) {
            status = -1;
            perror("fork");
            exit(1);
            return;
        }
        else if(pid == 0) {
            status = open(this -> fileName.c_str(), O_RDONLY);
            if(status == -1) {
                status = -1;
                perror("open");
                exit(1);
                return;
            }
            if(close(0)) {
                status = -1;
                perror("close");
                exit(1);
                return;
            }
            if(dup(status) == -1) {
                status = -1;
                perror("dup");
                exit(1);
                return;
            }
            this -> Left -> execute(status,pipes,In,Out,size);
            exit(0);
        }
        else {
            if(wait(&status) == -1)
                perror("wait");
                return;
        }
    }
}
