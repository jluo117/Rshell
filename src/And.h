#ifndef AND_H
#define AND_H
#include "Connector.h"
#include <stack>
class And :public Connector{
    public:
    And();
    And(Base *left);
    ~And();
    void fetch_name();
    void add_left(Base *left);
    void add_right(Base *right);
    void execute(int &status,int pipes[],bool In,bool Out, int &size);
    void execute();
    void toStack(std::stack <Base*> &stacker);
};
#endif
