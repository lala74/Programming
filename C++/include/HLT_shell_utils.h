// 05/03/2020: Created by Minh-Duc-LA
#ifndef __HLT_SHELL_UTILS_H
#define __HLT_SHELL_UTILS_H

#include <string>

using namespace std;

string HLT_execute_cmd_getOutput(string cmd);
int HLT_execute_cmd(string cmd, string PREFIX);
int HLT_copy(string src, string dst, string option);
int HLT_remove(string path, string option);
bool HLT_does_path_exist(const string& s);

#endif /* __HLT_SHELL_UTILS_H */