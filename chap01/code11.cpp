#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

#define MAX_WORDS 1000
#define MAX_LEN 20

string words[MAX_WORDS];
int n = 0;

string trim(string str);

int main()
{
    ifstream in_file("input.txt");

    string str;
    while(!in_file.eof()) {
        in_file >> str;
        str = trim(str);
        if (str.size() < 2) continue;
        int i=0;
        for (; i<n; i++) {
            if (str == words[i])
                break;
        }
        if (i == n)     // not found
            words[n++] = str;
    }

    for (int i=0; i<n; i++)
        cout << words[i] << endl;
    return 0;
}

string trim(string str) {
    while(str.size() > 0 && !isalnum(str.back()))
        str.pop_back();

    for (char &c: str)
        c = tolower(c);
    return str;
}