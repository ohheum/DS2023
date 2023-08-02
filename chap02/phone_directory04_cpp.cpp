#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

typedef struct {
    string name;
    string number;
    string email;
    string group;
} Person;

vector<Person> directory;

void handle_add(string);
void find(string);
void status();
void remove(string);
void load(string);
void save(string);
void add(string, string, string, string);
vector<string> split_line(string basicString, char dim);

int main() {

    string command_line;

    while (1) {
        cout << "$ ";
        getline(cin, command_line);
        if (command_line.size() <= 0)
            continue;

        vector<string> tokens = split_line(command_line, ' ');
        if (tokens[0] == "read") {
            if (tokens.size() != 2) {
                cout << "Invalid command format." << endl;
                continue;
            }
            load(tokens[1]);
        }
        else if (tokens[0] == "add") {
            if (tokens.size() != 2) {
                cout << "Invalid command format." << endl;
                continue;
            }
            handle_add(tokens[1]);
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

vector<string> split_line(string line, char dim=' ')
{
    vector <string> tokens;
    stringstream sstream(line);
    string str;

    while(getline(sstream, str, dim))
        tokens.push_back(str);
    return tokens;
}

void load(string fileName) {
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
        vector<string> tokens = split_line(line, '#');
        add(tokens[0], tokens[1], tokens[2], tokens[3]);
    }
    in_file.close();
}

void save(string fileName) {
    ofstream out_file(fileName);
    if (out_file.fail()) {
        cout << "File open failed." << endl;
        return;
    }

    for (Person p : directory) {
        out_file << p.name << "#";
        out_file << (p.number.size()==0 ? " " : p.number) << "#";
        out_file << (p.email.size()==0 ? " " : p.email) << "#";
        out_file << (p.group.size()==0 ? " " : p.group) << "#" << endl;
    }
    out_file.close();
}

int search(string name) {
    for (int i=0; i<directory.size(); i++) {
        if (name == directory[i].name) {
            return i;
        }
    }
    return -1;
}

void remove(string name) {
    int i = search(name);  /* returns -1 if not exists */
    if (i == -1) {
        cout << "No person named " << name << " exists." << endl;
        return;
    }
    directory.erase(directory.begin() + i);
    cout << name << " was deleted successfully." << endl;
}

void print_person(Person p)
{
    cout << p.name << ":" << endl;
    cout << "   Phone: " << p.number << endl;
    cout << "   Email: " << p.email << endl;
    cout << "   Group: " << p.group << endl;
}

void status() {
    for (int i=0; i<directory.size(); i++)
        print_person(directory[i]);
    cout << "Total " << directory.size() << " persons." << endl;
}

void find(string name) {
    int index = search(name);
    if (index==-1)
        cout << "No person named " << name << " exists." << endl;
    else
        print_person(directory[index]);
}

void handle_add(string name)  {
    string number, email, group;
    char empty[] = " ";

    cout << "  Phone: ";
    getline(cin, number);;
    cout << "  Email: ";
    getline(cin, email);;
    cout << "  Group: ";
    getline(cin, group);;

    add(name, number,  email,  group);
}

void add(string name, string number, string email, string group) {
    Person p = { name, number, email, group};
    int i = 0;
    for (; i<directory.size() && directory[i].name <= name; i++);
    directory.insert(directory.begin() + i, p);
    cout << name << " was added successfully." << endl;
}



