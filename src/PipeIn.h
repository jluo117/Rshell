#ifndef PIPE_H
#define PIPE_H
#include <string>
#include "Connector.h"
class PipeIn: public Connector{
    std::string fileName;
    public:
    PipeIn(std::string filename);
    ~PipeIn();
    void fetch_name();
    void add_left(Base *left);
    void add_right(Base *right);
    void execute(int &status,int pipes[],bool In,bool Out);
};
#endif
