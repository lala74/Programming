/*
 * File: HLT_Cprocess.h
 * Project: Learning test for C++
 * Date: Friday, 28th August 2020 9:32:32 am
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#ifndef __HLT_C_PROCESS_H_
#define __HLT_C_PROCESS_H_

#include <string>
#include <unistd.h>
#include <glib.h>

class HLT_Cprocess
{
    private:
        GPid m_pid;
        gsize m_nbArgs;
        bool m_bProcessAlreadyRun;
        gchar **m_argv;
    public:
        HLT_Cprocess(std::string argv[], gsize sz);
        ~HLT_Cprocess();
        int run();
        int wait();
        int close();
};

#endif