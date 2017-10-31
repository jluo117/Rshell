#ifndef BASE_H
#define BASE_H
class Base{
    public:
        bool IsComplete;
        virtual bool execute() = 0;
        virtual void add_right(Base *right) = 0;
};
#endif
