#ifdef _WIN32
    #include <windows.h>
#endif
#include <iostream>
#include <vector>
#include "../headers/hospital.h"
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>






bool Hospital::login(string input_email, string input_password) {
    ifstream file("CSV_Files/hospital_info.csv");
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
void Hospital::openCSV_blood_inventory_info()
{
 const string filename = "CSV_Files/blood_inventory.csv";
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}
void Hospital::readBloodInventory()
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    string line;
    cout << "\nBlood Inventory:\n";
    cout << "-----------------\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    cout << "-----------------\n";
    file.close();
}
void Hospital::addBlood(const string &bloodGroup, int amount)
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    vector<pair<string, int>> inventory;
    string line, bg;
    int amt;
    bool found = false;

    // Read the CSV file into a vector
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, bg, ',');
        if (getline(ss, line, ',')) {
            amt = stoi(line);
        } else {
            amt = 0;
        }

        if (bg == bloodGroup) {
            amt += amount;
            found = true;
        }

        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found) {
        cout << "Error: Blood group not found.\n";
        return;
    }

    // Write back the updated inventory
    ofstream outFile("CSV_Files/blood_inventory.csv");
    for (const auto &entry : inventory) {
        outFile << entry.first << "," << entry.second << "\n";
    }
    outFile.close();

    cout << "Successfully added " << amount << " bags to " << bloodGroup << " blood group.\n";
}

void Hospital::removeBlood(const string &bloodGroup, int amount)
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    vector<pair<string, int>> inventory;
    string line, bg;
    int amt;
    bool found = false;

    // Read the CSV file into a vector
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, bg, ',');
        if (getline(ss, line, ',')) {
            amt = stoi(line);
        } else {
            amt = 0;
        }

        if (bg == bloodGroup) {
            if (amt < amount) {
                cout << "Error: Not enough blood bags available. Current: " << amt << "\n";
                file.close();
                return;
            }
            amt -= amount;
            found = true;
        }

        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found) {
        cout << "Error: Blood group not found.\n";
        return;
    }

    // Write back the updated inventory
    ofstream outFile("CSV_Files/blood_inventory.csv");
    for (const auto &entry : inventory) {
        outFile << entry.first << "," << entry.second << "\n";
    }
    outFile.close();

    cout << "Successfully removed " << amount << " bags from " << bloodGroup << " blood group.\n";
}