#ifndef BASE_H
#define BASE_H
class Base{
    public:
        bool IsValid;
        bool IsComplete;
        virtual void execute() = 0;
        virtual void add_right(Base *right) = 0;
};
#endif
