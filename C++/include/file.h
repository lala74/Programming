#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <string>

using namespace std;

int file_write(string PATH, string content);
string file_read_content(string PATH);

#endif