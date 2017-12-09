#include <iostream>
#include "Or.h"
Or::Or(){
    this -> IsConnector = true;
    this -> Left = 0;
    this -> Right = 0;
}
Or::Or(Base *left){
    this -> Left = left;
    this -> Right = 0;
}
Or::~Or(){
    delete this -> Right;
    delete this -> Left;
}
//error call
void Or::fetch_name(){
    std::cout << "parse error near " << "'||'" << std::endl;
}
void Or::add_right(Base *right){
    this -> Right = right;
}
void Or::add_left(Base *left){
    this -> Left = left;
}
void Or::execute(int &status,int pipes[],bool In, bool Out, int &size){
    int opt = 0;
    size = 0;
    if ((this -> Right == 0) || (this -> Left == 0)){
       std::cout << "missing arguement" << std::endl;
       status = -1;
       return;
   }
    this -> Left -> execute(opt,pipes,false,false,size);
    size = 0;
    if (opt != 0){
        opt = 0;
        this -> Right -> execute(opt,pipes,false,false,size);
        status = opt;
        return;
    }
        status = 0;
        return;
}
void Or::toStack(std::stack <Base*> &stacker){
    stacker.push(this);
}
void Or::execute(){
    this -> Left -> execute();
    this -> Right -> execute();
}
