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
bool And::execute(){
    if ((this -> right == 0) || (this -> left == 0)){
        std::cout << "missing arguemnet" << std::endl;
        return false;
    }

        if(this -> left -> execute()){
            if (this -> right -> execute()){
                return true;
            }
            else{
                return false;
            }
         }
        else{
            return false;
        }

}

