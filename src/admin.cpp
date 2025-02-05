//admin.cpp

#ifdef _WIN32
    #include <windows.h>
#endif

#include "../headers/admin.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>




void Admin::openCSV_admin_info() {
    const string filename = "CSV_Files/admin_info.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}





Admin::Admin(string u_name, string u_email, string pass ) :
User(u_name, u_email, pass){ }

bool Admin::login(string input_email, string input_password) {
    ifstream file("CSV_Files/admin_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open user data file!" << endl;
        return false;
    }

    string line, stored_username, stored_email, stored_password;
    
    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');

        if (stored_email== input_email && stored_password == input_password) {
            file.close();
            return true;  // Login successful
        }
    }

    file.close();
    return false;  // Login failed
}


void Admin::Register_Admin(string input_user_name, string input_email, string input_password) {
    ifstream file("CSV_Files/admin_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open user data file!" << endl;
        return;
    }

    string line, stored_username, stored_email, stored_password;
    
    // Check if username or email already exists
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');


        if (stored_email == input_email) {
            cerr << "Error: Email already exists!" << endl;
            file.close();
            return;
        }
    }
    
    file.close(); // Close input file before writing

    // Open file in append mode to add a new user
    ofstream outfile("CSV_Files/admin_data.csv", ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open user data file for writing!" << endl;
        return;
    }

    // Write new user data to the file
    outfile << input_user_name << "," << input_email << "," << input_password << endl;
    outfile.close();

    cout << "User registered successfully!" << endl;
}

void Admin::Register_Moderator(string input_user_name, string input_email, string input_password) {
    
    
    ifstream file("CSV_Files/moderator_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open user data file!" << endl;
        return;
    }

    string line, stored_username, stored_email, stored_password;
    
    // Check if username or email already exists
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');

        if (stored_email == input_email) {
            cerr << "Error: Email already exists!" << endl;
            file.close();
            return;
        }
    }
    
    file.close(); // Close input file before writing

    // Open file in append mode to add a new user
    ofstream outfile("CSV_Files/moderator_data.csv", ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open user data file for writing!" << endl;
        return;
    }

    // Write new user data to the file
    outfile << input_user_name << "," << input_email << "," << input_password << endl;
    outfile.close();

    cout << "User registered successfully!" << endl;
}

void Admin::openCSV_blood_inventory_info()
{
 const string filename = "CSV_Files/blood_inventory.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}


void Admin::openCSV_donor_info()
{
     const string filename = "CSV_Files/donor_info.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}

void Admin::openCSV_hospital_info()
{
     const string filename = "CSV_Files/hospital_info.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}

void Admin::openCSV_moderator_info()
{
     const string filename = "CSV_Files/moderator_data.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}