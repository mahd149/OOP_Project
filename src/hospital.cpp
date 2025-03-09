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
#include <string>
#include <ctime>
#include <unordered_map>

bool Hospital::login(string input_email, string input_password)
{
    ifstream file("CSV_Files/hospital_info.csv");
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

void Hospital::readBloodInventory()
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open())
    {
        cout << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    string line;
    cout << "\nBlood Inventory:\n";
    cout << "-----------------\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    cout << "-----------------\n";
    file.close();
}
string normalizeBloodGroup(const string &bg)
{
    string result = bg;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void Hospital::addDonor(Donor &donor)
{
    // Save the donor information to the donor_info.csv file
    string filename = "CSV_Files/donor_info.csv";
    donor.saveToFile(filename);
}

void Hospital::addBlood(int donorId)
{
    ifstream donorFile("CSV_Files/donor_info.csv");
    if (!donorFile.is_open())
    {
        cerr << "Error: Could not open CSV_Files/donor_info.csv\n";
        return;
    }

    string line;
    bool donorFound = false;
    string donorName, bloodGroup;
    Donor newDonor;

    // Search for the donor by ID in the donor_info.csv
    while (getline(donorFile, line))
    {
        stringstream ss(line);
        string temp;
        int currentId;

        getline(ss, temp, ','); // Read the ID
        currentId = stoi(temp); // Convert to integer

        // Check if it matches the given donor ID
        if (currentId == donorId)
        {
            donorFound = true;
            getline(ss, donorName, ',');  // Read the donor's name
            getline(ss, bloodGroup, ','); // Read the blood group
            break;
        }
    }

    donorFile.close();

    // If donor is not found, ask if the user wants to create a new donor
    if (!donorFound)
    {
        char choice;
        cout << "Donor with ID " << donorId << " not found. Do you want to create a new donor? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            
            newDonor.inputDonor();  // Get input from the user for new donor
                 // Add the new donor to the system

            donorFound = true;
            donorName = newDonor.getName();  
            bloodGroup = newDonor.getBloodGroup();  
        }
        else
        {
            cout << "No new donor created. Exiting...\n";
            return;
        }
    }

    // Prompt user for the number of bags needed
    int amount;
    cout << "Donor " << donorName << " (Blood Group: " << bloodGroup << ") found.\n";
    cout << "Enter number of bags of blood to take: ";
    cin >> amount;
    Bloodtest* b = new Surgical(bloodGroup,amount,"Hospital_name");

    if (!b->initial_test())
    {
        cout << "**Blood failed the safety tests! Cannot be added to inventory.**\n";
        return;
    }

    // Continue with the existing blood inventory update logic
    else{
        addDonor(newDonor);
        ifstream file("CSV_Files/blood_inventory.csv");
        if (!file.is_open())
        {
            cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
            return;
        }
    
        vector<pair<string, int>> inventory;
        bool found = false;
        string bg;
        int amt;
    
        // Read the CSV file into a vector
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, bg, ',');
    
            if (getline(ss, line, ','))
            {
                try
                {
                    amt = stoi(line); // Ensure valid number conversion
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Error: Invalid number format in CSV file: " << line << endl;
                    amt = 0;
                }
            }
            else
            {
                amt = 0; // Default value if the field is missing
            }
    
            if (normalizeBloodGroup(bg) == normalizeBloodGroup(bloodGroup))
            {
                amt += amount;
                found = true;
            }
    
            inventory.push_back({bg, amt});
        }
        file.close();
    
        if (!found)
        {
            cerr << "Error: Blood group not found.\n";
            return;
        }
    
        // Write back the updated inventory
        ofstream outFile("CSV_Files/blood_inventory.csv");
        if (!outFile.is_open())
        {
            cerr << "Error: Could not open CSV_Files/blood_inventory.csv for writing.\n";
            return;
        }
    
        for (const auto &entry : inventory)
        {
            outFile << entry.first << "," << entry.second << "\n";
        }
        outFile.close();
    
        // Open detailed_blood_inventory.csv and append new entries
        ofstream detailFile("CSV_Files/detailed_blood_inventory.csv", ios::app);
        if (!detailFile.is_open())
        {
            cerr << "Error: Could not open CSV_Files/detailed_blood_inventory.csv for writing.\n";
            return;
        }
    
        time_t currentTime = time(0);
        for (int i = 0; i < amount; i++)
        {
            detailFile << bloodGroup << "," << currentTime + i << "\n"; // Assign unique timestamps per bag
        }
        detailFile.close();
    
        cout << "Successfully added " << amount << " bags to " << bloodGroup << " blood group.\n";

    }

}


unordered_map<string, int> Hospital::checkExpiry(int minutes)
{
    ifstream detailFile("CSV_Files/detailed_blood_inventory.csv");
    if (!detailFile.is_open())
    {
        cerr << "Error: Could not open CSV_Files/detailed_blood_inventory.csv\n";
        return {};
    }

    unordered_map<string, int> expiredBloodCount;
    string line, bloodGroup;
    time_t timestamp;
    time_t currentTime = time(nullptr);

    while (getline(detailFile, line))
    {
        stringstream ss(line);
        getline(ss, bloodGroup, ',');
        ss >> timestamp;

        if (timestamp + minutes * 60 < currentTime)
        {
            expiredBloodCount[normalizeBloodGroup(bloodGroup)]++;
        }
    }
    detailFile.close();

    if (expiredBloodCount.empty())
    {
        cout << "No blood units expired within " << minutes << " minutes.\n";
    }
    else
    {
        cout << "Expired blood records:\n";
        for (const auto &entry : expiredBloodCount)
        {
            cout << "Blood Group: " << entry.first << " | Amount: " << entry.second << " bags\n";
        }
    }

    return expiredBloodCount;
}

void Hospital::removeBlood(const string &bloodGroup, int amount)
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    vector<pair<string, int>> inventory;
    string line, bg;
    int amt;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, bg, ',');

        getline(ss, line, ',');
        amt = (line.empty()) ? 0 : stoi(line); 

        if (normalizeBloodGroup(bg) == normalizeBloodGroup(bloodGroup))
        {
            if (amt < amount)
            {
                cerr << "Error: Not enough blood bags available. Current: " << amt << "\n";
                file.close();
                return;
            }
            amt -= amount;
            found = true;
        }

        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found)
    {
        cerr << "Error: Blood group not found.\n";
        return;
    }

    // Write back the updated inventory
    ofstream outFile("CSV_Files/blood_inventory.csv");
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv for writing.\n";
        return;
    }

    for (const auto &entry : inventory)
    {
        outFile << entry.first << "," << entry.second << "\n";
    }
    outFile.close();

    // --- Remove oldest `amount` entries from detailed_blood_inventory.csv ---
    ifstream detailFile("CSV_Files/detailed_blood_inventory.csv");
    if (!detailFile.is_open())
    {
        cerr << "Error: Could not open CSV_Files/detailed_blood_inventory.csv\n";
        return;
    }

    vector<pair<string, time_t>> detailedRecords;
    vector<pair<string, time_t>> filteredRecords;
    int removedCount = 0;

    while (getline(detailFile, line))
    {
        stringstream ss(line);
        string bgroup;
        time_t timestamp;

        getline(ss, bgroup, ',');
        ss >> timestamp;

        detailedRecords.push_back({bgroup, timestamp});
    }
    detailFile.close();

    // Sort records by timestamp (oldest first)
    sort(detailedRecords.begin(), detailedRecords.end(), [](const auto &a, const auto &b)
         { return a.second < b.second; });

    // Remove oldest `amount` entries for the given blood group
    for (const auto &entry : detailedRecords)
    {
        if (removedCount < amount && normalizeBloodGroup(entry.first) == normalizeBloodGroup(bloodGroup))
        {
            removedCount++;
        }
        else
        {
            filteredRecords.push_back(entry);
        }
    }

    // Write back remaining entries
    ofstream newDetailFile("CSV_Files/detailed_blood_inventory.csv");
    if (!newDetailFile.is_open())
    {
        cerr << "Error: Could not open CSV_Files/detailed_blood_inventory.csv for writing.\n";
        return;
    }

    for (const auto &entry : filteredRecords)
    {
        newDetailFile << entry.first << "," << entry.second << "\n";
    }
    newDetailFile.close();

    cout << "Successfully removed " << amount << " bags from " << bloodGroup << " blood group.\n";
}

string Hospital::trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

void Hospital::searchBlood()
{
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

    while (getline(file, line))
    {
        stringstream ss(line);
        string id,name, bg, age, area_zip, contact;

        getline(ss, id, ',');
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
void Hospital::processBloodRequest(Bloodtest *request)
{
    cout << "\n[Processing Request] Checking availability for " << request->getQuantity()
         << " units of " << request->getBloodGroup() << "...\n";

    request->performTests();

    if (request->approveRequest())
    {
        cout << "[Success] Blood request approved!\n";
        removeBlood(request->getBloodGroup(), request->getQuantity());
    }
    else
    {
        cout << "[Failed] Blood request **not approved** due to test failure.\n";
    }
}
void Hospital::requestBlood(const string &bloodGroup, int amount, bool isSurgical)
{
    cout << "\n[Blood Request] Requesting " << amount << " units of " << bloodGroup;
    cout << (isSurgical ? " for **Surgical use**.\n" : " for **Non-Surgical use**.\n");

    Bloodtest* request;

    if (isSurgical)
    {
        request = new Surgical(bloodGroup, amount, "Hospital_Name");
    }
    else
    {
        request = new NonSurgical(bloodGroup, amount, "Hospital_Name");
    }

    processBloodRequest(request);

    delete request;
}

