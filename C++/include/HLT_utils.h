// 22/11/2019: Created by C. Silveira
#ifndef __HLT_UTILS_H
#define __HLT_UTILS_H

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
extern const int HLT_kDebug;
const char szHLT[] = "** HLT ";
const char szHLT_INFO[] = "** HLT Info: ";
const char szHLT_DEBUG[] = "** HLT Debug: ";
const char szHLT_ERROR[] = "** HLT Error: ";

// Terminal colors
// Escape is: \033
// Color code is: [0;31m
const char szHLT_TERM_COLOR_ERROR[] = "\033\[1;41;37m";
const char szHLT_TERM_COLOR_RESET[] = "\033[0m";

#define HLT_throw(arg) throw HLT_exception(arg, __FILE__, __LINE__, __FUNCTION__);

class HLT_exception : public std::exception
{
    std::string message;

public:
    HLT_exception(const std::string& msg_, const char* file_, int line_, const char* func_, const char* info_ = "")
        : std::exception()
    {
        std::ostringstream o;
        o << szHLT << "Exception:" << file_ << ":" << line_ << ":" << func_ << ": " << msg_ << ": " << info_;
        message = o.str();
    }
    const char* what() const noexcept { return message.c_str(); }
};

inline void HLT_Msg(const std::string&& type_, const std::string& msg_, const char* file_, int line_, const char* func_)
{
    if(type_ == "Error") cout << szHLT_TERM_COLOR_ERROR;
    cout << szHLT << type_ << ": " << file_ << ":" << line_ << ":" << func_ << ": " << msg_;
    if(type_ == "Error") cout << szHLT_TERM_COLOR_RESET;
    cout << endl;
}
#define HLT_errMsg(arg) HLT_Msg("Error", arg, __FILE__, __LINE__, __FUNCTION__);
inline void HLT_dbgMsg(const std::string& msg_)
{
    if(HLT_kDebug) {
        cout << szHLT_DEBUG << msg_ << endl;
    }
}
inline void HLT_infMsg(const std::string& msg_)
{
    cout << szHLT_INFO << msg_ << endl;
}

#endif /* __HLT_UTILS_H */
