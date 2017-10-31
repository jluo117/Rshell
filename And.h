#ifndef AND_H
#define AND_H
#include "Connector.h"
class And :public Connector{
    public:
    And(Base *left);
    void add_right(Base *right);
    bool execute();
};
#endif
