#ifndef OR_H
#define OR_H
#include "Connector.h"
class Or: public Connector{
    public:
        Or();
        Or(Base *left);
        ~Or();
        void fetch_name ();
        void add_right(Base *right);
        void add_left(Base *left);
        void  execute(int &status);
};

#endif
