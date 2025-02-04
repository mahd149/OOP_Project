// moderator.cpp

#include "moderator.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#endif

void Moderator::openCSV_donor_info() {
    const string filename = "CSV_Files/donor_info.csv"; // Declare the filename outside the #ifdef block

    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}


bool Moderator::login(string input_username, string input_password) {
    ifstream file("CSV_Files/moderator_data.csv");
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

        if (stored_username == input_username && stored_password == input_password) {
            file.close();
            return true;  // Login successful
        }
    }

    file.close();
    return false;  // Login failed
}