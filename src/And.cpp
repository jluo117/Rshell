#include <unistd.h>
#include <iostream>
#include "And.h"
And::And(){
    this -> IsConnector = true;
    this -> Left = 0;
    this -> Right = 0;
}
And::And(Base *left){
    this -> IsConnector = true;
    this -> Left = left;
    this -> Right = 0;
}
And::~And(){
    delete this -> Left;
    delete this -> Right;
}
void And::add_left(Base *left){
    this -> Left = left;
}
void And::add_right(Base *right){
    this -> Right = right;
}
void And::fetch_name(){
    std::cout<< "parse error near " << "'&&'" << std::endl;
}
void And::execute(int &status){
    if ((this -> Right == 0) || (this -> Left == 0)){
        std::cout << "missing arguemnet" << std::endl;
        status = -1;
        return;
    }
        int curState = 0;
        this -> Left -> execute(curState);
        if (curState != -0){
            status = -1;
            return;
        }
        this -> Right -> execute(curState);
        if (curState != 0){
            status = -1;
            return;
        }
        status = 0;
        return;
}

