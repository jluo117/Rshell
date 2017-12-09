#ifndef BASE_H
#define BASE_H
#include <stack>
class Base{
    public:
        int inDir;
        int outDir;
        virtual ~Base(){}
        bool IsConnector = false;
        bool Double = false;
        bool IsSpecial = false;
        Base *Left;
        Base *Right;
        virtual void fetch_name ()=0;
        virtual void execute(int &status,int pipes[],bool In, bool Out, int &size) = 0;
        virtual void execute() = 0;
        virtual void add_left(Base*) = 0;
        virtual void add_right(Base*)= 0;
        virtual void toStack(std::stack <Base*> &stacker) = 0;
};
#endif
