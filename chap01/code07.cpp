#include <iostream>
#include <string>

using namespace std;

int main () {
    string s1("hello");
    string s2 = "hello";
    string s3 = string("hello");
    string s4{"hello"};
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    return 0;
}