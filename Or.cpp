#include <iostream>
#include "Or.h"
Or::Or(){
    this -> IsConnector = true;
    this -> left = 0;
    this -> right = 0;
}
Or::Or(Base *left){
    this -> IsConnector = true;
    this -> left = left;
    this -> right = 0;
}
void Or::add_right(Base *right){
    this -> right = right;
}
void Or::add_left(Base *left){
    this -> left = left;
}
bool Or::execute(){
   if ((this -> right == 0) || (this -> left == 0)){
       std::cout << "missing arguement" << std::endl;
       return false;
   }
    if (this -> left -> execute()){
        return true;
    }
    else{
       if (this -> right -> execute()){
          return true;
       }
       else{
          return false;
       }
}
}
