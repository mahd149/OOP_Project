//search.h

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>




//separate the implementation in .cpp file please


using namespace std;

class Search
{
public:
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }
    void searchBlood()
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
};