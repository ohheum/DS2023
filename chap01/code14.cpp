#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    while (1) {
        cout << "$ ";
        getline(cin, line);
        if (line == "exit")
            break;
        cout << line << ":" << line.size() << endl;
    }
    return 0;
}