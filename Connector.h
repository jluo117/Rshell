#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Base.h"
class Connector: public Base{
    public:
        virtual bool execute() = 0;
        virtual void add_left(Base*)= 0;
        virtual void add_right(Base*) = 0;
};
#endif
