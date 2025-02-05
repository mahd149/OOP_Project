#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "headers/users.h"

using namespace std;

int main()
{
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Search for Blood\n2. Admin Login\n3. Moderator Login\n4. Hospital Login\n0. Exit\n";

        int x;
        cout << "Enter option: ";
        cin >> x;

        if (cin.fail())
        { // Handle non-integer input
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (x)
        {
        case 1:
        {
            // Enclosing in {} prevents jump error
            Search s;
            s.searchBlood();
            break;
        }
        case 2:
        {
            //Admin menu
            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;
            Admin* a = new Admin("", email, password);

            if(a->login(email, password))
            {
                cout<<"Login successful!\n";
                //additional code for admin options
            }
            else 
            {
                cout<<"Invalid username or password!\n";
            }

            break;
        }
            
        case 3:
        {
            //Moderator menu
            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;
            Moderator* m = new Moderator("", email, password);
            if(m->login(email, password))
            {
                cout<<"Login successful!\n";
                //additional code for moderator options
            }
            else 
            {
                cout<<"Invalid username or password!\n";
            }


            break;
        }

        
        case 0:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}


/* how to compile the program example

g++ -Iinclude -c src/file1.cpp -o file1.o
g++ -Iinclude -c src/file2.cpp -o file2.o
g++ -c main.cpp -o main.o

g++ file1.o file2.o main.o -o output_program


./output_program.exe

*/