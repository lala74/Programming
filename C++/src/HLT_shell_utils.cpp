// 05/03/2020: Created by Minh-Duc-LA

#include <iostream>
#include <string>
#include <sys/stat.h>
#include "HLT_utils.h"
#include "HLT_shell_utils.h"

using namespace std;

static string build_option(string option)
{
	if (option.find_first_not_of(' ') == string::npos) {
	// option is null or full of space
		return "";
	} else {
		return ("-" + option);
	}
}

string HLT_execute_cmd_getOutput(string cmd)
{
	FILE *fp=NULL;
	char Response[256];
	string result;

	fp = popen(cmd.c_str(), "r");
	if (fp == NULL) {
		HLT_throw("FP=NULL");
		return "-1";
	}

	while (fgets(Response, sizeof(Response), fp) != NULL) {
		result += Response;
	}
	pclose(fp);
	return result;
}

int HLT_execute_cmd(string cmd, string PREFIX)
{
	string Response;
	int iRet=0;
		
	Response = HLT_execute_cmd_getOutput(cmd);

	if (Response != "" && Response != "-1") {
		cout << PREFIX << "\033\[1;41;37m Error : \n" << Response << "\033\[0m";
		iRet = -2;
	}
	if (Response == "-1") {
		iRet = -1;
	}

    return iRet;
}

int HLT_copy(string src, string dst, string option)
{
	string cmd, opt;

	opt = build_option(option);
	cmd = "cp " + opt + " " + src + " " + dst;
	return HLT_execute_cmd(cmd, "HLT_copy");
}

int HLT_remove(string path, string option)
{
	string cmd, opt;

	opt = build_option(option);
	cmd = "rm " + opt + " " + path;
	return HLT_execute_cmd(cmd, "HLT_remove");
}

bool HLT_does_path_exist(const string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
