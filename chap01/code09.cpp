#include <iostream>
#include <string>

using namespace std;

int main () {
    string str ("Welcome to the string world in C++ !!!");
    char cstr[100];         // 혹은 char *cstr = new char [100];

    strcpy(cstr, str.c_str());
    cout << cstr << endl;
    string str2(cstr);
    cout << str2 << endl;
    return 0;
}