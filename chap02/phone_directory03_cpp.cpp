#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

vector<string> names;           /* names */
vector<string> numbers;         /* phone numbers 051-234-6787 */

void load(string);
void add(string, string);
void find(string);
void status();
void remove(string);
void save(string);
vector<string> split_line(string basicString);

int main() {
    string command_line;
    string command;
    while (1) {
        cout << "$ ";
        getline(cin, command_line);
        if (command_line.size() <= 0)
            continue;

        vector<string> tokens = split_line(command_line);
        if (tokens[0] == "read") {
            if (tokens.size() != 2) {
                cout << "Invalid command format." << endl;
                continue;
            }
            load(tokens[1]);
        }
        else if (tokens[0] == "add") {
            if (tokens.size() != 3) {
                cout << "Invalid command format." << endl;
                continue;
            }
            add(tokens[1], tokens[2]);
        }
        else if (tokens[0] == "find") {
            if (tokens.size() != 2) {
                cout << "Invalid command format." << endl;
                continue;
            }
            find(tokens[1]);
        }
        else if (tokens[0] == "status") {
            status();
        }
        else if (tokens[0] == "delete") {
            if (tokens.size() != 2) {
                cout << "Invalid command format." << endl;
                continue;
            }
            remove(tokens[1]);
        }
        else if (tokens[0] == "save") {
            if (tokens.size() != 3) {
                cout << "Invalid command format." << endl;
                continue;
            }
            save(tokens[2]);
        }
        else if (tokens[0] == "exit")
            break;
    }
    return 0;
}

vector<string> split_line(string line)
{
    vector <string> tokens;
    stringstream check(line);
    string str;

    while(getline(check, str, ' '))
        tokens.push_back(str);
    return tokens;
}

void load(string fileName)
{
    ifstream in_file(fileName);
    if (in_file.fail()) {
        cout << "File not found." << endl;
        return;
    }
    string line;
    while (!in_file.eof()) {
        getline(in_file, line);
        if (line.size() <= 0)
            break;
        vector<string> tokens = split_line(line);
        add(tokens[0], tokens[1]);
    }
    in_file.close();
}

void save(string fileName)
{
    ofstream out_file(fileName);
    for (int i=0; i<names.size(); i++)
        out_file << names[i] << " " << numbers[i] << endl;
    out_file.close();
}

void add(string name, string number) {
    int i=0;
    for (; i<names.size() && names[i] <= name; i++);
    names.insert(names.begin() + i, name);
    numbers.insert(numbers.begin() + i, number);
    cout << name << " was added successfully." << endl;
}

void find(string name) {
    for (int i=0; i<names.size(); i++) {
        if (name == names[i]) {
            cout << numbers[i] << endl;
            return;
        }
    }
    cout << "No person named " << name << " exists." << endl;
}

void status() {
    for (int i=0; i<names.size(); i++)
        cout << names[i] << ' ' << numbers[i] << endl;
    cout << "Total " << names.size() << " persons." << endl;
}

void remove(string name) {
    for (int i=0; i<names.size(); i++) {
        if (name == names[i]) {
            names.erase(names.begin() + i);
            numbers.erase(numbers.begin() + i);
            cout << name << " was deleted successfully." << endl;
            return;
        }
    }
    cout << "No person named " << name << " exists." << endl;
}

// using iterator
void remove_iter() {
    string name;
    cin >> name;

    vector<string>::iterator iter1, iter2;
    for(iter1 = names.begin(), iter2 = numbers.begin(); iter1 != names.end(); iter1++, iter2++) {
        if (*iter1 == name) {
            names.erase(iter1);
            numbers.erase(iter2);
            cout << name << " was deleted successfully." << endl;
            return;
        }
    }
    cout << "No person named " << name << " exists." << endl;
}