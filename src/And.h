#ifndef AND_H
#define AND_H
#include "Connector.h"
class And :public Connector{
    public:
    And();
    And(Base *left);
    void fetchName ();
    void add_left(Base *left);
    void add_right(Base *right);
    void execute(int &status);
};
#endif
