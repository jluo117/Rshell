#ifndef BASE_H
#define BASE_H
class Base{
    protected:
        bool IsValid;
        virtual void execute() = 0;
};
#endif
