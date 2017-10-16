#ifndef
#define
#include <iostream>
class command{
    private:
        std::string baseFunction;
        std::vector<string> comdArg;
    public:
        command(vector<string> &comdArg);
        ~command();
        exacute();
}

#endif
