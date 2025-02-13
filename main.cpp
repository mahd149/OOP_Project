#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>
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
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (x)
        {
        case 1:
        {
            Search s;
            s.searchBlood();
            break;
        }
        case 2: // admin login menu
        {
            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;

            Admin *a = new Admin("", email, password);

            if (a->login(email, password))
            {
                cout << "Login successful!\n";
                int choice;
                while (true)
                {
                    cout << "1. Open Files\n";
                    
                    cout << "2. Register Admin\n";
                    cout << "3. Register Moderator\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (choice == 1)
                    {
                        while(true)
                        {
                            int x;
                            cout << "1. Open Admin info File\n";
                            cout << "2. Open Moderator File\n";
                            cout << "3. Open Donor File\n";
                            cout << "4. Open Blood Inventory File\n";
                            cout << "5. Open Hospital File\n";
                            cout << "0. Exit\n";
                            cout << "Enter your choice: ";
                            cin >> x;

                            if(x == 1)
                                a->openCSV_admin_info();
                            else if (x == 2)
                                a->openCSV_moderator_info();
                            else if (x == 3)
                                a->openCSV_donor_info();
                            else if (x == 4)
                                a->openCSV_blood_inventory_info();
                            else if (x == 5)
                                a->openCSV_hospital_info();
                            else if(x == 0)
                                break;
                            else cout<<"Invalid choice!\n";
                        }
                    }
                    
                    else if (choice == 2)
                    {
                        string name, email, pass;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter name: ";
                        // cin >> name;
                        getline(cin, name);
                        cout << "Enter email: ";
                        cin >> email;
                        cout << "Enter password: ";
                        cin >> pass;
                        a->Register_Admin(name, email, pass);
                    }
                    else if (choice == 3)
                    {
                        string name, email, pass;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter name: ";
                        getline(cin, name);
                        cout << "Enter email: ";
                        cin >> email;
                        cout << "Enter password: ";
                        cin >> pass;
                        a->Register_Moderator(name, email, pass);
                    }
                    else if (choice == 0)
                        break;
                    else
                        cout << "Invalid choice! Try again." << endl;
                }
            }
            else
                cout << "Invalid username or password!\n";

            delete a;
            break;
        }
        case 3: // moderator login menu
        {
            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;

            Moderator *m = new Moderator("", email, password);

            if (m->login(email, password))
            {
                cout << "Login successful!\n";
                int choice;
                while (true)
                {
                    cout << "1. Open Donor Files\n";
                    cout << "2. Open Blood Inventory\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (choice == 1)
                        m->openCSV_donor_info();
                    else if (choice == 2)
                        m->openCSV_bloodBank_info();
                    else if (choice == 0)
                        break;
                    else
                        cout << "Invalid choice! Try again." << endl;
                }
            }
            else
                cout << "Invalid username or password!\n";

            delete m;
            break;
        }
        case 4: // hospital login menu
        {

            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;

            Hospital *h = new Hospital();

            if (h->login(email, password))
            {
                cout << "Login successful!\n";
                int choice;
                while (true)
                {
                    cout << "1. Read Blood Inventory\n";
                    cout << "2. Add Blood\n";
                    cout << "3. Remove Blood\n";
                    cout << "4. Search Blood\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (choice == 1)
                        h->readBloodInventory();
                    else if (choice == 2)
                    {
                        string bloodGroup;
                        int amount;
                        cout << "Enter Blood Group: ";
                        cin >> bloodGroup;
                        cout << "Enter Amount: ";
                        cin >> amount;
                        h->addBlood(bloodGroup, amount);
                    }
                    else if (choice == 3)
                    {
                        string bloodGroup;
                        int amount;
                        cout << "Enter Blood Group: ";
                        cin >> bloodGroup;
                        cout << "Enter Amount: ";
                        cin >> amount;
                        h->removeBlood(bloodGroup, amount);
                    }
                    else if (choice == 4)
                        h->searchBlood();
                    else if (choice == 0)
                        break;
                    else
                        cout << "Invalid choice! Try again." << endl;
                }
            }
            else
                cout << "Invalid username or password!\n";

            delete h;
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

g++ -Iheader -c src/file1.cpp -o file1.o
g++ -Iheader -c src/file2.cpp -o file2.o
g++ -c main.cpp -o main.o

g++ file1.o file2.o main.o -o main


./main.exe

*/

/*
g++ main.cpp src/*.cpp -Iheaders -Wall -Wextra -o Blood_Bank.exe

./output.exe
*/