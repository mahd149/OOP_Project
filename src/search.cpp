#include "../headers/search.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string Search::trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

void Search::searchBlood() {
    string blood_group, zip;
    cout << "Enter Blood Group: ";
    cin >> blood_group;
    cout << "Enter Area ZIP: ";
    cin >> zip;

    transform(blood_group.begin(), blood_group.end(), blood_group.begin(), ::toupper);

    ifstream file("CSV_Files/donor_info.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open CSV_Files/donor_info.csv\n";
        return;
    }

    vector<string> exactMatches, areaMatches;
    string line;

    zip = trim(zip);
    int zipCode = stoi(zip);
    char area;

    // Determine the area based on the user's ZIP input
    if (zipCode >= 0 && zipCode <= 2000)
        area = 'A';
    else if (zipCode <= 4000)
        area = 'B';
    else if (zipCode <= 6000)
        area = 'C';
    else if (zipCode <= 8000)
        area = 'D';
    else
        area = 'E';

    while (getline(file, line)) {
        stringstream ss(line);
        string dummy, name, bg, age, area_zip, contact;

        // Skip first column if needed
        getline(ss, dummy, ',');  // Assuming the first column is an ID

        // Read columns (adjusted positions)
        getline(ss, name, ',');  // 2nd column: Name
        getline(ss, bg, ',');    // 3rd column: Blood Group
        getline(ss, age, ',');   // 4th column: Age
        getline(ss, area_zip, ','); // 5th column: ZIP
        getline(ss, contact, ',');  // 6th column: Contact

        name = trim(name);
        bg = trim(bg);
        area_zip = trim(area_zip);
        contact = trim(contact);

        transform(bg.begin(), bg.end(), bg.begin(), ::toupper);
        int donorZip = stoi(area_zip);

        string donorInfo = "Name: " + name + "\nBlood Group: " + bg + "\nContact: " + contact + "\n----------------------------------------\n";

        // Check for exact match (blood group and zip code)
        if (bg == blood_group) {
            if (area_zip == zip) {
                exactMatches.push_back(donorInfo);  // Exact match: same zip code
            } else {
                // Determine donor's area
                char donorArea;
                if (donorZip >= 0 && donorZip <= 2000)
                    donorArea = 'A';
                else if (donorZip <= 4000)
                    donorArea = 'B';
                else if (donorZip <= 6000)
                    donorArea = 'C';
                else if (donorZip <= 8000)
                    donorArea = 'D';
                else
                    donorArea = 'E';

                if (donorArea == area) {
                    areaMatches.push_back(donorInfo);  // Area match: same area but different zip code
                }
            }
        }
    }

    file.close();

    // Output exact matches (same ZIP code)
    if (!exactMatches.empty()) {
        cout << "\nMatching Donors in ZIP " << zip << ":\n";
        cout << "----------------------------------------\n";
        for (const string &donor : exactMatches) {
            cout << donor;
        }
    } else {
        cout << "No donors found in ZIP " << zip << " for Blood Group " << blood_group << ".\n";
    }

    // Output area matches (same blood group, same area but different ZIP code)
    if (!areaMatches.empty()) {
        cout << "\nOther matching donors in the same area:\n";
        cout << "----------------------------------------\n";
        for (const string &donor : areaMatches) {
            cout << donor;
        }
    }
}
