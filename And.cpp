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
    if ((this -> right -> IsValid) && (this -> left -> IsValid)){
        this -> IsValid = true;
    }
    else{
        this -> IsValid = false;
    }
}
void And::execute(){
    if ((this -> right == 0) || (this -> left == 0)){
        std::cout << "missing arguemnet" << std::endl;
        return;
    }
    try{
        this -> left -> execute();
    }
    catch(int i){
        return;
    }
    try{
        this -> right -> execute();
    }
    catch(int i){
        return;
    }
}
