#include "../headers/search.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string Search::trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

void Search::searchBlood(const string &bloodGroup, const string &zip, vector<string> &results) 
{
    results.clear();
    ifstream file("CSV_Files/donor_info.csv");
    if (!file.is_open())
    {
        results.push_back("Error: Could not open CSV file.");
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, bg, age, area_zip, contact, timestamp;

        // Read all 7 fields correctly
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, bg, ',');
        getline(ss, age, ',');
        getline(ss, area_zip, ',');
        getline(ss, contact, ',');
        getline(ss, timestamp, ',');

        // Trim and clean input
        name = trim(name);
        bg = trim(bg);
        area_zip = trim(area_zip);
        contact = trim(contact);
        timestamp = trim(timestamp);

        // Convert blood group input to uppercase for case-insensitive comparison
        string bg_upper = bg;
        transform(bg_upper.begin(), bg_upper.end(), bg_upper.begin(), ::toupper);
        
        string searchBG = bloodGroup;
        transform(searchBG.begin(), searchBG.end(), searchBG.begin(), ::toupper);

        if (bg_upper == searchBG && area_zip == zip)
        {
            results.push_back("Name: " + name + " | Contact: " + contact);
        }
        
        // Debugging output
        //cout << "Checking: " << name << " | BG: " << bg_upper << " | ZIP: " << area_zip << endl;
    }
    file.close();

    if (results.empty())
    {
        results.push_back("No donors found.");
    }
}
