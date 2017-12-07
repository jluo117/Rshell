#ifndef REDIRECT_H
#define REDIRECT_H
#include "Connector.h"
class ReDirect: public Connector{
    public:
        ReDirect();
        ~ReDirect();
        void fetch_name ();
        void execute (int &status,int pipes[],bool In, bool Out, int &size);
        void add_left(Base*);
        void add_right(Base*);
};
#endif
