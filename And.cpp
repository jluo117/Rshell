#include <iostream>
#include "And.h"
And::And(Base *left, Base *right){
    this -> left = left;
    this -> right = right;
    if (left -> IsValid && right -> IsValid){
        this -> IsValid = true;
    }
}

void And::execute(){
    try{
        this -> left -> execute();
    }
    catch{
        return;
    }
    try{
        this -> right -> execute();
    }
    catch{
        return;
    }
}
