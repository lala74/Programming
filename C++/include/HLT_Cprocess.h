#ifndef __HLT_C_PROCESS_H_
#define __HLT_C_PROCESS_H_

#include <glib.h>
#include <unistd.h>
#include <string>

class HLT_Cprocess
{
private:
    GPid m_pid;
    gsize m_nbArgument;
    std::string* m_argv;

public:
    HLT_Cprocess(std::string argv[], gsize sz);
    ~HLT_Cprocess();
    int run();
    void wait();
    int close();
};

#endif