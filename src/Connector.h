#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Base.h"
class Connector: public Base{
    public:
        ~Connector(){}
        virtual void fetch_name () = 0;
        virtual void execute(int &status,int pipes[],bool In,bool Out ,int &size) = 0;
        virtual void add_left(Base*)= 0;
        virtual void add_right(Base*) = 0;
};
#endif
