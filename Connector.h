#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Base.h"
class Connector: public Base{
    protected:
        Base *left;
        Base *right;
    public:
        virtual void execute() = 0;
};
#endif
