#include <unistd.h>
#include <iostream>
#include "And.h"
And::And(Base *left){
    this -> left = left;
    this -> right = 0;
    this -> IsComplete = false;
}
void And::add_right(Base *right){
    this -> right = right;
    this -> IsComplete = true;
}
bool And::execute(){
    if ((this -> right == 0) || (this -> left == 0)){
        std::cout << "missing arguemnet" << std::endl;
        return false;
    }

        if(this -> left -> execute()){
            this -> right -> execute();
         }
        else{
            return false;
        }
        return true;

}

