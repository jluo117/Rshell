#include <unistd.h>
#include <iostream>
#include "And.h"
And::And(){
    this -> IsConnector = true;
    this -> left = 0;
    this -> right = 0;
}
And::And(Base *left){
    this -> IsConnector = true;
    this -> left = left;
    this -> right = 0;
}
void And::add_left(Base *left){
    this -> left = left;
}
void And::add_right(Base *right){
    this -> right = right;
}
void And::execute(int &status){
    if ((this -> right == 0) || (this -> left == 0)){
        std::cout << "missing arguemnet" << std::endl;
        status = -1;
        return;
    }
        int curState = 0;
        this -> left -> execute(curState);
        if (curState != -0){
            status = -1;
            return;
        }
        this -> right -> execute(curState);
        if (curState != 0){
            status = -1;
            return;
        }
        status = 0;
        return;
}

