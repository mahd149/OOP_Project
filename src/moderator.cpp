// moderator.cpp

#ifdef _WIN32
#include <windows.h>
#endif

#include "../headers/moderator.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

void Moderator::openCSV_donor_info()
{
    const string filename = "CSV_Files/donor_info.csv"; // Declare the filename outside the #ifdef block

#ifdef _WIN32
    char fullPath[MAX_PATH];
    GetFullPathName(filename.c_str(), MAX_PATH, fullPath, NULL);
    ShellExecute(nullptr, "open", fullPath, nullptr, nullptr, SW_SHOWNORMAL);
#else
    string command = "xdg-open " + filename + " &";
    system(command.c_str());
#endif
}

void Moderator::openCSV_bloodBank_info()
{
    const string filename = "CSV_Files/blood_inventory.csv"; // Declare the filename outside the #ifdef block

#ifdef _WIN32
    char fullPath[MAX_PATH];
    GetFullPathName(filename.c_str(), MAX_PATH, fullPath, NULL);
    ShellExecute(nullptr, "open", fullPath, nullptr, nullptr, SW_SHOWNORMAL);
#else
    string command = "xdg-open " + filename + " &";
    system(command.c_str());
#endif
}

Moderator::Moderator(string u_name, string u_email, string pass) : User(u_name, u_email, pass) {}

bool Moderator::login(string input_email, string input_password)
{
    ifstream file("CSV_Files/moderator_data.csv");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open user data file!" << endl;
        return false;
    }

    string line, stored_username, stored_email, stored_password;

    // Read the file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');

        if (stored_email == input_email && stored_password == input_password)
        {
            file.close();
            return true; // Login successful
        }
    }

    file.close();
    return false; // Login failed
}