#ifndef BASE_H
#define BASE_H
class Base{
    public:
        bool IsConnector;
        Base *left;
        Base *right;
        virtual bool execute() = 0;
        virtual void add_left(Base*) = 0;
        virtual void add_right(Base*)= 0;
};
#endif
