#ifndef BASE_H
#define BASE_H
class Base{
    public:
        virtual ~Base(){}
        bool IsConnector;
        bool IsSpecial = false;
        Base *Left;
        Base *Right;
        virtual void fetch_name ()=0;
        virtual void execute(int &status,bool In, bool Out) = 0;
        virtual void add_left(Base*) = 0;
        virtual void add_right(Base*)= 0;
};
#endif
