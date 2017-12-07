#ifndef BASE_H
#define BASE_H
class Base{
    public:
        virtual ~Base(){}
        bool IsConnector = false;
        bool Double = false;
        bool IsSpecial = false;
        Base *Left;
        Base *Right;
        virtual void fetch_name ()=0;
        virtual void execute(int &status,int pipes[],bool In, bool Out, int &size) = 0;
        virtual void add_left(Base*) = 0;
        virtual void add_right(Base*)= 0;
};
#endif
