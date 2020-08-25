#ifndef __HLT_C_STRING_H_
#define __HLT_C_STRING_H_

#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class CString
{
private:
    int age;
    string m_name;
    vector<int> model;

public:
    CString();
    CString(const string& name);

    string getName();
    void test();
};

#endif