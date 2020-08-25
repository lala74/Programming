#include <CString.h>
#include <iostream>
#include <string>

using namespace std;

CString::CString() : model(8)
{
    age = 0;
    m_name = "";
}

CString::CString(const string& name)
{
    m_name = name;
    // age = 10;
}

string CString::getName()
{
    return m_name;
}

void CString::test()
{
    cout << "This is test function" << endl;
    model[0] = 5;
    cout << "model 0: " << model[0] << endl;
    cout << "size: " << model.size() << endl;
}
