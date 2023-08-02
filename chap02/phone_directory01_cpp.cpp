#include <string>
#include <iostream>

using namespace std;

vector<string> names;           /* names */
vector<string> numbers;         /* phone numbers 051-234-6787 */

void add();
void find();
void status();
void remove();

int main() {
    string command;
    while (1) {
        cout << "$ ";
        cin >> command;

        if (command == "add")
            add();
        else if (command == "find")
            find();
        else if (command == "status")
            status();
        else if (command == "delete")
            remove();
        else if (command == "exit")
            break;
    }
    return 0;
}

void add() {
    string name, number;
    cin >> name >> number;
    names.push_back(name);
    numbers.push_back(number);
    cout << name << " was added successfully." << endl;
}

void find() {
    string name;
    cin >> name;
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

void remove() {
    string name;
    cin >> name;

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