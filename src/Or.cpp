#include <iostream>
#include "Or.h"
Or::Or(){
    this -> IsConnector = true;
    this -> left = 0;
    this -> right = 0;
}
Or::Or(Base *left){
    this -> left = left;
    this -> right = 0;
}
Or::~Or(){
    delete this -> right;
    delete this -> left;
}
//error call
void Or::fetchName(){
    std::cout << "parse error near " << "'||'" << std::endl;
}
void Or::add_right(Base *right){
    this -> right = right;
}
void Or::add_left(Base *left){
    this -> left = left;
}
void Or::execute(int &status){
    int opt = 0;
    if ((this -> right == 0) || (this -> left == 0)){
       std::cout << "missing arguement" << std::endl;
       status = -1;
       return;
   }
    this -> left -> execute(opt);
    if(opt == -999){
        status = -999; //used for force exit
        exit(0);
    }
    if (opt != 0){
        opt = 0;
        this -> right -> execute(opt);
        status = opt;
        return;
    }
    else if (opt == 0){
        status = 0;
        return;
    }

}
