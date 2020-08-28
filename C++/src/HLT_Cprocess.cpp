/*
 * File: HLT_Cprocess.cpp
 * Project: Learning test for C++
 * Date: Friday, 28th August 2020 9:32:32 am
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */
#include <string.h>

#include <string>
#include <iostream>
#include <sys/wait.h>
#include <signal.h>

#include "HLT_Cprocess.h"
#include "HLT_utils.h"

using namespace std;

HLT_Cprocess::HLT_Cprocess(string argv[], gsize sz):
m_pid(-1),
m_nbArgs(sz),
m_bProcessAlreadyRun(FALSE)
{
    m_argv = new gchar*[m_nbArgs+1];
    for (uint i=0; i < m_nbArgs; i++) {
        m_argv[i] = g_strdup(argv[i].c_str());
    }
    m_argv[m_nbArgs] = NULL;
}

HLT_Cprocess::~HLT_Cprocess()
{
    // void    
}

int HLT_Cprocess::run()
{
    if ( !m_bProcessAlreadyRun ) {
        GError *pError = nullptr;
        GPid child_pid = -1;

        g_spawn_async (NULL, m_argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, &child_pid, &pError);
        if (pError != NULL) {
            cout << szHLT_ERROR << "Error while spawning child: " << pError->message << endl;
            g_error_free(pError);
            return -1;
        }
        m_pid = child_pid;
        m_bProcessAlreadyRun = TRUE;
    } else {
        HLT_dbgMsg("Process altready run");
    }
    return 0;
}

int HLT_Cprocess::wait()
{
    if ( !m_bProcessAlreadyRun ){
        HLT_errMsg("Cannot wait a non-running process");
        return -1;
    }

    if (m_pid >= 0) {
        waitpid(m_pid, NULL, 0);
    }
    return 0;
}

int HLT_Cprocess::close()
{
    int iRet = -1;
    if ( !m_bProcessAlreadyRun ){
        HLT_errMsg("Cannot close a non-running process");
        return iRet;
    }
    // Send kill signal + close process
    if (m_pid >= 0) {
        if (kill(m_pid, SIGKILL) >= 0) {
            iRet = 0;
        }
        g_spawn_close_pid (m_pid);
    }
    // Free all arguments of process
    if (m_argv != NULL) {
        for (uint i=0; i<m_nbArgs; i++) {
            g_free(m_argv[i]);
        }
        g_free(m_argv);
    }
    return iRet;
}
