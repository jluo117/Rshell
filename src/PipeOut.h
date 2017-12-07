#ifndef PIPEOUT_H
#define PIPEOUT_H
#include <string>
#include "Connector.h"
class PipeOut :public Base{
    std::string fileName;
    bool append;
    public:
        PipeOut(std::string targetFile,bool append);
        ~PipeOut();
        void fetch_name();
        void execute(int &status,int pipes[], bool In,bool Out,int &size);
        void add_left(Base*);
        void add_right(Base*);
};
#endif
