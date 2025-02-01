#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "headers/users.h"

using namespace std;

int main() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Search for Blood\n2. Hospital login\n3. Admin Login\n0. Exit\n";

        int x;
        cout << "Enter option: ";
        cin >> x;

        if (cin.fail()) {  // Handle non-integer input
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (x) {
            case 1: {
                // Enclosing in {} prevents jump error
                Search s;
                s.searchBlood();
                break;
            }
            case 2:
                cout << "Hospital login...\n";
                break;
            case 3:
                cout << "Admin login...\n";
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}
