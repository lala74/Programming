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
m_nbArgument(sz)
{
    m_argv = argv;
}

HLT_Cprocess::~HLT_Cprocess()
{
    // void    
}

int HLT_Cprocess::run()
{
    GError *pError = nullptr;
    gchar *argv[m_nbArgument+1];
    GPid child_pid = -1;

    for (uint i=0; i < m_nbArgument; i++) {
        argv[i] = g_strdup(m_argv[i].c_str());
    }
    argv[m_nbArgument] = NULL;

    g_spawn_async (NULL, argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, &child_pid, &pError);
    if (pError != NULL) {
        cout << szHLT_ERROR << "Error while spawning child: " << pError->message << endl;
        g_error_free(pError);
        return -1;
    }

    m_pid = child_pid;
    cout << "create child process " << m_pid << endl;
    return 0;
}

void HLT_Cprocess::wait()
{
    cout << "wait process " << m_pid << endl;
    waitpid(m_pid, NULL, 0);
    return;
}

int HLT_Cprocess::close()
{
    int iRet = -1;
    // if (m_argv != NULL) {
    //     g_free(m_argv);
    // }
    if (kill(m_pid, SIGKILL) >= 0) {
        iRet = 0;
    }
    g_spawn_close_pid (m_pid);
    return iRet;
}
