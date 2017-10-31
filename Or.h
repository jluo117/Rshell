#ifndef OR_H
#define OR_H
#include "Connector.h"
class Or: public Connector{
    public:
        Or(Base *left);
        void add_right(Base *right);
        bool execute();
};

#endif
