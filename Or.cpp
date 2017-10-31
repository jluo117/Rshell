#include "Or.h"
Or::Or(Base *left){
    this -> left = left;
    this -> IsComplete = false;
}
void Or::add_right(Base *right){
    this -> right = right;
    this -> IsComplete = true;
}
bool Or::execute(){
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
