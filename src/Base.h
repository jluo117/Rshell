#ifndef BASE_H
#define BASE_H
class Base{
    public:
        virtual ~Base(){}
        bool IsConnector;
        Base *left;
        Base *right;
        virtual void fetchName ()=0;
        virtual void execute(int &status) = 0;
        virtual void add_left(Base*) = 0;
        virtual void add_right(Base*)= 0;
};
#endif
