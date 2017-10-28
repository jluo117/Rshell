#ifndef AND_H
#define AND_H
#include "Connector.h"
class And :protected Connector{
    protected:
    And(Base *left, Base *right);
    void execute();
};
#endif
