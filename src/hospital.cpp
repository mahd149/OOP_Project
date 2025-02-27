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
#include<string>






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
string normalizeBloodGroup(const string &bg) {
    string result = bg;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void Hospital::addBlood(const string &bloodGroup, int amount)
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
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
            try {
                amt = stoi(line); // Ensure valid number conversion
            } catch (const invalid_argument &e) {
                cerr << "Error: Invalid number format in CSV file: " << line << endl;
                amt = 0;
            }
        } else {
            amt = 0; // Default value if the field is missing
        }

        if (normalizeBloodGroup(bg) == normalizeBloodGroup(bloodGroup)) {
            amt += amount;
            found = true;
        }

        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found) {
        cerr << "Error: Blood group not found.\n";
        return;
    }

    // Write back the updated inventory
    ofstream outFile("CSV_Files/blood_inventory.csv");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv for writing.\n";
        return;
    }

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
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
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
            try {
                amt = stoi(line); // Handle conversion errors
            } catch (const invalid_argument &e) {
                cerr << "Error: Invalid number format in CSV file: " << line << endl;
                amt = 0;
            }
        } else {
            amt = 0; // Default value if missing
        }

        if (normalizeBloodGroup(bg) == normalizeBloodGroup(bloodGroup)) {
            if (amt < amount) {
                cerr << "Error: Not enough blood bags available. Current: " << amt << "\n";
                file.close();
                return; // Prevent writing back changes if insufficient blood
            }
            amt -= amount;
            found = true;
        }

        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found) {
        cerr << "Error: Blood group not found.\n";
        return;
    }

    // Write back the updated inventory
    ofstream outFile("CSV_Files/blood_inventory.csv");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv for writing.\n";
        return;
    }

    for (const auto &entry : inventory) {
        outFile << entry.first << "," << entry.second << "\n";
    }
    outFile.close();

    cout << "Successfully removed " << amount << " bags from " << bloodGroup << " blood group.\n";
}



// void Hospital::openCSV_blood_inventory_info()
// {
//  const string filename = "CSV_Files/blood_inventory.csv";
//     #ifdef _WIN32
//         ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
//     #else
//         string command = "xdg-open " + filename + " &";
//         system(command.c_str());
//     #endif
// }


// using namespace std;

string Hospital::trim(const string &str){
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

void Hospital:: searchBlood(){
     string blood_group, zip;
        cout << "Enter Blood Group: ";
        cin >> blood_group;
        cout << "Enter Area zip: ";
        cin >> zip;

        // Convert blood group to uppercase for better matching
        transform(blood_group.begin(), blood_group.end(), blood_group.begin(), ::toupper);

        ifstream file("CSV_Files/donor_info.csv"); // Update path if necessary
        if (!file.is_open())
        {
            cout << "Error: Could not open CSV_Files/donor_info.csv\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nMatching Donors:\n";
        cout << "----------------------------------------\n";

        while(getline(file, line))
        {
            stringstream ss(line);
            string name, bg, age, area_zip, contact;

            getline(ss, name, ',');
            getline(ss, bg, ',');
            getline(ss, age, ',');
            getline(ss, area_zip, ',');
            getline(ss, contact, ',');

            // Trim spaces from fields
            name = trim(name);
            bg = trim(bg);
            age = trim(age);
            area_zip = trim(area_zip);
            contact = trim(contact);

            // Convert CSV blood group to uppercase before comparison
            transform(bg.begin(), bg.end(), bg.begin(), ::toupper);

            if (bg == blood_group && area_zip == zip)
            {
                cout << "Name: " << name << "\n";
                cout << "Blood Group: " << bg << "\n";
                cout << "Age: " << age << "\n";
                cout << "ZIP Code: " << area_zip << "\n";
                cout << "Contact: " << contact << "\n";
                cout << "----------------------------------------\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "No donors found for Blood Group " << blood_group << " in ZIP " << zip << ".\n";
        }

        file.close();
    }
    void Hospital::processBloodRequest(RequestBlood *request) {
        cout << "\n[Processing Request] Checking availability for " << request->getQuantity() 
             << " units of " << request->getBloodGroup() << "...\n";
    
        request->performTests(); 
    
        if (request->approveRequest()) {
            cout << "[Success] Blood request approved!\n";
            removeBlood(request->getBloodGroup(), request->getQuantity());
        } else {
            cout << "[Failed] Blood request **not approved** due to test failure.\n";
        }
    }
    void Hospital::requestBlood(const string &bloodGroup, int amount, bool isSurgical) {
        cout << "\n[Blood Request] Requesting " << amount << " units of " << bloodGroup;
        cout << (isSurgical ? " for **Surgical use**.\n" : " for **Non-Surgical use**.\n");
    
        RequestBlood *request;
        
        if (isSurgical) {
            request = new Surgical(bloodGroup, amount, "Hospital_Name"); 
        } else {
            request = new NonSurgical(bloodGroup, amount, "Hospital_Name"); 
        }
    
        processBloodRequest(request);
        
        delete request;  
    }
    
