#ifndef BASE_H
#define BASE_H
class Base{
    public:
        bool IsComplete;
        virtual bool execute() = 0;
};
#endif
