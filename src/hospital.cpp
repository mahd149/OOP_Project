/* #ifdef _WIN32
#include <windows.h>
#endif */

#include "../headers/hospital.h"
#include "../headers/bloodtest.h"
#include "../headers/surgical.h"
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int Hospital::lastId = 0;

vector<string> Hospital::readBloodInventory()
{
    vector<string> bloodData; // Store the inventory data

    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open())
    {
        cout << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return bloodData; // Return empty vector if file can't be opened
    }

    string line;
    while (getline(file, line))
    {
        bloodData.push_back(line);
    }

    file.close();
    return bloodData; // Return the collected data
}

string Hospital::normalizeBloodGroup(string bg)
{
    transform(bg.begin(), bg.end(), bg.begin(), ::toupper);
    if (bg == "A+" || bg == "A-" || bg == "B+" || bg == "B-" ||
        bg == "AB+" || bg == "AB-" || bg == "O+" || bg == "O-")
    {
        return bg;
    }
    return "";
}

vector<string> Hospital::bloodyTimeTracker()
{
    vector<string> result;
    currentTime = time(0);
    cout << "Time Elapsed = " << (120 - (currentTime - lastDonationTime)) << endl;
    if (donorFound && lastDonationTime != 0 && (currentTime - lastDonationTime) < 120)
    {
        cout << "You must wait " << (120 - (currentTime - lastDonationTime)) << " more seconds before donating blood again.\n";
        result.push_back("You must wait " + to_string(120 - (currentTime - lastDonationTime)) + " more seconds before donating blood again.");
    }
    // result.push_back("You must wait " + to_string(120 - (currentTime - lastDonationTime)) + " more seconds before donating blood again.");
    return result; // empty means fine
}

void Hospital::write_to_inventory(int amount, string bloodGroup)
{
    ifstream file("CSV_Files/blood_inventory.csv");
    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV_Files/blood_inventory.csv\n";
        return;
    }

    vector<pair<string, int>> inventory;
    bool found = false;
    string line, bg, amtStr;
    int amt;

    while (getline(file, line))
    {
        stringstream ss(line);

        if (!getline(ss, bg, ','))
            continue; // Read blood group (skip empty lines)
        if (!getline(ss, amtStr, ','))
            continue; // Read amount as string (skip invalid lines)

        // Handle empty or invalid numeric fields
        if (amtStr.empty())
        {
            cerr << "Warning: Missing blood amount in line: " << line << endl;
            continue;
        }

        try
        {
            amt = stoi(amtStr); // Convert to integer
        }
        catch (const std::exception &e)
        {
            cerr << "Error: Invalid number in line: " << line << " -> " << amtStr << endl;
            continue; // Skip invalid entries
        }

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

void Hospital::write_details(int amount, Donor d, vector<string> donorRecords, int donorID)
{
    currentTime = time(0);

    // Print records before updating
    cout << "Records BEFORE updating:\n";
    for (const auto &record : donorRecords)
    {
        cout << record << "\n";
    }
    cout << "----------------------------\n";

    // Append to detailed_blood_inventory.csv
    ofstream detailFile("CSV_Files/detailed_blood_inventory.csv", ios::app);
    if (!detailFile.is_open())
    {
        cerr << "Error: Could not open detailed_blood_inventory.csv for appending.\n";
        return;
    }
    for (int i = 0; i < amount; i++)
        detailFile << d.getBloodGroup() << "," << currentTime + i << "\n";
    detailFile.close();

    // Now, update donor info if the donor already exists (based on donorID)
    bool donorExists = false;
    vector<string> updatedRecords;

    ifstream donorInFile("CSV_Files/donor_info.csv");
    if (!donorInFile.is_open())
    {
        cerr << "Error: Could not open donor_info.csv for reading.\n";
        return;
    }

    string line;
    while (getline(donorInFile, line))
    {
        stringstream ss(line);
        string field;
        int id;

        // Extract donorID from the first field (assuming CSV structure: id,name,bloodGroup,age,zip,contact,timestamp)
        getline(ss, field, ',');
        id = stoi(field); // Convert the first field to an integer (donor ID)

        if (id == donorID) // If the donor exists, update the timestamp
        {
            donorExists = true;
            string updatedLine = line;
            size_t pos = updatedLine.rfind(","); // Find the last comma (timestamp position)
            if (pos != string::npos)
            {
                updatedLine = updatedLine.substr(0, pos + 1) + to_string(currentTime); // Replace timestamp
            }
            updatedRecords.push_back(updatedLine);
        }
        else
        {
            updatedRecords.push_back(line); // Keep the record as is for non-matching donors
        }
    }
    donorInFile.close();

    // If donor exists, write back updated donor info
    if (donorExists)
    {
        // Write all records back to donor_info.csv (with updated timestamp)
        ofstream donorOutFile("CSV_Files/donor_info.csv", ios::trunc); // Use ios::trunc to overwrite the file
        if (!donorOutFile.is_open())
        {
            cerr << "Error: Could not open donor_info.csv for writing.\n";
            return;
        }
        for (const auto &record : updatedRecords)
        {
            donorOutFile << record << "\n";
        }
        donorOutFile.close();

        cout << "Successfully updated timestamp for donor ID " << donorID << "\n";
    }
    else
    {
        cout << "Donor ID " << donorID << " not found. No update performed.\n";
    }

    // Print records after updating
    cout << "Records AFTER updating:\n";
    for (const auto &record : donorRecords)
    {
        cout << record << "\n";
    }
    cout << "----------------------------\n";
}

void Hospital::write_details(int amount, Donor d, vector<string> donorRecords)
{
    currentTime = time(0);
    cout << "Records BEFORE updating:\n";
    for (const auto &record : donorRecords)
    {
        cout << record << "\n";
    }
    cout << "----------------------------\n";

    ofstream detailFile("CSV_Files/detailed_blood_inventory.csv", ios::app);
    if (!detailFile.is_open())
    {
        cerr << "Error: Could not open detailed_blood_inventory.csv for appending.\n";
        return;
    }
    for (int i = 0; i < amount; i++)
        detailFile << d.getBloodGroup() << "," << currentTime + i << "\n";
    detailFile.close();

    stringstream updatedRecord;
    updatedRecord << d.getId() << "," << d.getName() << "," << d.getBloodGroup() << "," << d.getAge() << "," << d.getZip() << "," << d.getContact() << "," << currentTime;
    donorRecords.clear();
    donorRecords.push_back(updatedRecord.str());

    // Print records after updating
    cout << "Records AFTER updating:\n";
    for (const auto &record : donorRecords)
    {
        cout << record << "\n";
    }
    cout << "----------------------------\n";

    ofstream donorOutFile("CSV_Files/donor_info.csv", ios::app);
    if (!donorOutFile.is_open())
    {
        cerr << "Error: Could not open donor_info.csv for writing.\n";
        return;
    }
    for (const auto &record : donorRecords)
        donorOutFile << record << "\n";
    donorOutFile.close();

    cout << "Successfully added " << amount << " bags to " << d.getBloodGroup() << " blood group.\n";
}
bool Hospital::bloodyTester(string bloodGroup, int amount)
{
    Bloodtest *b = new Surgical(bloodGroup, amount, "Hospital_name");
    if (!b->initial_test())
    {
        bloodTypingResult = b->getBloodTypingResults();
        cout << "bloodTypingResult Size = " << bloodTypingResult.size() << endl;
        infectionScreeningResults = b->getInfectionScreeningResults();
        hemoglobinLevelResults = b->getHemoglobinLevelResults();
        cout << "**Blood failed the safety tests! Cannot be added to inventory.**\n";
        return false;
    }
    bloodTypingResult = b->getBloodTypingResults();
    cout << "bloodTypingResult Size = " << bloodTypingResult.size() << endl;
    infectionScreeningResults = b->getInfectionScreeningResults();
    hemoglobinLevelResults = b->getHemoglobinLevelResults();
    return true;
}

vector<string> Hospital::addBlood(int donorId)
{
    if (donorId == -1)
        donorId = 1231231;
    cout << "DOnor ID = " << donorId << endl;
    vector<string> result; // Stores messages for GUI

    ifstream donorFile("CSV_Files/donor_info.csv");
    if (!donorFile.is_open())
    {
        result.push_back("Error: Could not open donor file.");
        return result;
    }

    string line;
    donorFound = false;
    string donorName, bloodGroup, contact, age, zip;
    vector<string> donorRecords;
    int currentId;

    while (getline(donorFile, line))
    {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        currentId = stoi(temp);

        // Always update lastId
        lastId = currentId;

        if (currentId == donorId)
        {
            donorFound = true;
            getline(ss, donorName, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, age, ',');
            getline(ss, zip, ',');
            getline(ss, contact, ',');

            if (getline(ss, temp, ',') && !temp.empty())
                lastDonationTime = stol(temp);

            bloodGroup = normalizeBloodGroup(bloodGroup);
            break;
        }

        donorRecords.push_back(line);
    }

    cout << "Last ID == " << lastId << endl;

    donorFile.close();

    // Now, lastId is guaranteed to have the last row ID

    if (!donorFound)
    {
        return result;
    }

    // Request blood amount
    result.push_back(donorName + "." + bloodGroup + "." + age + "." + zip + "." + contact);

    return result;
}
