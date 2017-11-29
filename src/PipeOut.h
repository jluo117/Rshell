#ifndef PIPEOUT_H
#define PIPEOUT_H
#include <string>
#include "Connector.h"
class PipeOut :public Connector{
    std::string targetFile;
    public:
        PipeOut(std::string targetFile);
        ~PipeOut();
        void fetch_name();
        void execute(int &status);
        void add_left(Base*);
        void add_right(Base*);
};
#endif
