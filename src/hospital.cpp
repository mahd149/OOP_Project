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
#include <set>

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
string normalizeBloodGroup(string bg)
{
    transform(bg.begin(), bg.end(), bg.begin(), ::toupper);
    if (bg == "A+" || bg == "A-" || bg == "B+" || bg == "B-" ||
        bg == "AB+" || bg == "AB-" || bg == "O+" || bg == "O-")
    {
        return bg;
    }
    return "";
}

void Hospital::addDonor(Donor &donor)
{
    // Save the donor information to the donor_info.csv file
    string filename = "CSV_Files/donor_info.csv";
    donor.saveToFile(filename);
}
void Hospital::write_to_inventory(int amount, string  bloodGroup){
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    vector<pair<string, int>> inventory;
    bool found = false;
    string bg;
    string line;
    int amt;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, bg, ',');
        getline(ss, line, ',');
        amt = stoi(line);
        if (normalizeBloodGroup(bg) == bloodGroup)
        {
            amt += amount;
            found = true;
        }
        inventory.push_back({bg, amt});
    }
    file.close();

    if (!found)
    {
        cerr << "Error: Blood group not found in inventory.\n";
        return;
    }

    ofstream outFile("CSV_Files/blood_inventory.csv");
    for (const auto &entry : inventory)
        outFile << entry.first << "," << entry.second << "\n";
    outFile.close();

    
}
void  Hospital::write_details(int amount,Donor d,time_t currentTime,vector<string>donorRecords){
    ofstream detailFile("CSV_Files/detailed_blood_inventory.csv", ios::app);
    for (int i = 0; i < amount; i++)
        detailFile << d.getBloodGroup() << "," << currentTime + i << "\n";
    detailFile.close();

    for (auto &record : donorRecords)
    {
        stringstream ss(record);
        string temp;
        getline(ss, temp, ',');
        if (stoi(temp) == d.getId())
        {
            stringstream updatedRecord;
            updatedRecord << temp << "," << d.getName() << "," << d.getBloodGroup() << "," << d.getAge() << "," << d.getZip() << "," << d.getContact() << "," << currentTime;
            record = updatedRecord.str();
        }
    }

    ofstream donorOutFile("CSV_Files/donor_info.csv", ios::trunc);
    for (const auto &record : donorRecords)
        donorOutFile << record << "\n";
    donorOutFile.close();

    cout << "Successfully added " << amount << " bags to " << d.getBloodGroup() << " blood group.\n";
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
    string donorName, bloodGroup, contact, age, zip;
    time_t lastDonationTime = 0;
    vector<string> donorRecords;
    int lastId = 0, currentId;
    set<int> validIds;

    // Read donor info
    while (getline(donorFile, line))
    {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ',');
        currentId = stoi(temp);
        lastId = currentId;
        validIds.insert(currentId);

        if (currentId == donorId)
        {
            donorFound = true;
            getline(ss, donorName, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, age, ',');
            getline(ss, zip, ',');
            getline(ss, contact, ',');
            getline(ss, temp, ',');
            if (!temp.empty())
                lastDonationTime = stol(temp);

            bloodGroup = normalizeBloodGroup(bloodGroup);
        }
        donorRecords.push_back(line);
    }
    donorFile.close();

    if (donorId == -1) // If user wants to create a new donor
    {
        donorFound = false; // Make sure we will create a new donor
    }
    else if (!validIds.count(donorId)) // If ID is not valid
    {
        while (true)
        {
            cout << "Invalid ID. Enter a valid ID or -1 to create a new donor: ";
            cin >> donorId;
            if (donorId == -1)
            {
                donorFound = false; // Allow creating new donor
                break;
            }
            if (validIds.count(donorId)) // If a valid ID is found
            {
                donorFound = true;
                break;
            }
        }
    }

    if (!donorFound) // If donor is not found, create new donor details
    {
        donorId = lastId + 1;

        cout << "Enter Donor Name: ";
        cin.ignore();
        getline(cin, donorName);

        while (true)
        {
            cout << "Enter Blood Group: ";
            getline(cin, bloodGroup);
            bloodGroup = normalizeBloodGroup(bloodGroup);
            if (!bloodGroup.empty())
                break;
            cout << "Invalid blood group. Please enter (A+, A-, B+, B-, AB+, AB-, O+, O-).\n";
        }

        while (true)
        {
            cout << "Enter Age (18 - 150): ";
            cin >> age;
            if (isdigit(age[0]) && stoi(age) >= 18 && stoi(age) <= 150)
                break;
            cout << "Invalid Age. Enter a number between 18 and 150.\n";
        }

        while (true)
        {
            cout << "Enter Zip Code (0 - 9999): ";
            cin >> zip;
            if (isdigit(zip[0]) && stoi(zip) >= 0 && stoi(zip) <= 9999)
                break;
            cout << "Invalid Zip Code. Enter a number between 0 and 9999.\n";
        }

        while (true)
        {
            cout << "Enter Contact Number (11 digits): ";
            cin >> contact;
            if (contact.length() == 11 && all_of(contact.begin(), contact.end(), ::isdigit))
                break;
            cout << "Invalid Contact. Must be exactly 11 digits.\n";
        }

        stringstream newRecord;
        newRecord << donorId << "," << donorName << "," << bloodGroup << "," << age << "," << zip << "," << contact << ",0";
        donorRecords.push_back(newRecord.str());

        cout << "Donor " << donorName << " (Blood Group: " << bloodGroup << ") created.\n";
        cout << "Contact: " << contact << " Zip: " << zip << "\n";
    }
    else // If donor is found, display their details
    {
        cout << "Donor " << donorName << " (Blood Group: " << bloodGroup << ") found.\n";
        cout << "Contact: " << contact << " Zip: " << zip << "\n";
    }
    Donor d(donorId,donorName,bloodGroup,stoi(age),stoi(zip),contact);

    time_t currentTime = time(0);
    if (lastDonationTime != 0 && (currentTime - lastDonationTime) < 120)
    {
        cout << "You must wait " << (120 - (currentTime - lastDonationTime)) << " more seconds before donating blood again.\n";
        return;
    }

    int amount;
    while (true)
    {
        cout << "Enter number of bags of blood to take (Max 3): ";
        cin >> amount;
        if (amount > 0 && amount <= 3)
        {
            break; // Exit the loop when a valid number is entered
        }
        else
        {
            cout << "Error: You can only donate 1, 2, or 3 bags. Please try again.\n";
        }
    }

    Bloodtest *b = new Surgical(bloodGroup, amount, "Hospital_name");
    if (!b->initial_test())
    {
        cout << "**Blood failed the safety tests! Cannot be added to inventory.**\n";
        return;
    }

   
    write_to_inventory(amount,bloodGroup);
    write_details(amount,d,currentTime,donorRecords);
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
        string id, name, bg, age, area_zip, contact;

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

    Bloodtest *request;

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
