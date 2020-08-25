// basic file operations
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int file_write(string PATH, string content)
{
  ofstream myfile;
  myfile.open(PATH);
  myfile << content;
  myfile.close();

  return 0;
}

string file_read_content(string PATH) 
{
  ifstream ifs(PATH);
  string content((istreambuf_iterator<char>(ifs)),
                 (istreambuf_iterator<char>()));

  if (content == "") {
    cout << "Can't get secret file content" << endl;
    return "-1";
  } else {
    content.pop_back();
    return content;
  }
}