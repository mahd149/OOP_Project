#include "donor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>  // For numeric limits (e.g., std::numeric_limits)
#include <cctype>  // For isdigit() function

using namespace std;

Donor::Donor()
{
    id = 0;
    name = "";
    bloodGroup = "";
    age = 0;
    zip = 0;
    contact = "";
}

void Donor::inputDonor()
{
    cout << "Enter Name: ";
    cin.ignore();  // Ignore any leftover characters from previous inputs
    getline(cin, name);
    
    cout << "Enter Blood Group: ";
    cin >> bloodGroup;
    
    // Validate age input: Ensure it's a valid positive integer
    cout << "Enter Age: ";
    while (true) {
        string ageInput;
        cin >> ageInput;
        
        if (isValidInteger(ageInput)) {
            age = stoi(ageInput);
            if (age > 0) break;  // Ensure age is positive
        }
        
        cout << "Invalid age. Please enter a valid positive number: ";
        cin.clear();  // Clears error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignores the rest of the input
    }
    
    // Validate zip code input: Ensure it's a valid positive integer
    cout << "Enter Zip Code: ";
    while (true) {
        string zipInput;
        cin >> zipInput;
        
        if (isValidInteger(zipInput)) {
            zip = stoi(zipInput);
            if (zip > 0) break;  // Ensure zip is positive
        }
        
        cout << "Invalid zip code. Please enter a valid positive number: ";
        cin.clear();  // Clears error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignores the rest of the input
    }
    
    cout << "Enter Contact: ";
    cin >> contact;
}

bool Donor::isValidInteger(const string &str)
{
    for (char c : str) {
        if (!isdigit(c)) return false;  // Return false if any character is not a digit
    }
    return true;  // Return true if all characters are digits
}

void Donor::saveToFile(const string &filename)
{
    ifstream file(filename);
    string line;
    int lastId = 0;  // Default to 0 if no file exists or is empty
    bool exists = false;

    // Check if the file exists and find the last id
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string temp;
            int currentId;

            // Read the id from the line
            getline(ss, temp, ',');
            currentId = stoi(temp); // Convert the id part to an integer

            // Update lastId to the most recent one
            lastId = currentId;

            // Check if the donor already exists by comparing each field
            stringstream donorData(line);
            string donorName, donorBloodGroup, donorAge, donorZip, donorContact;
            getline(donorData, temp, ','); // Skip the ID
            getline(donorData, donorName, ',');
            getline(donorData, donorBloodGroup, ',');
            getline(donorData, donorAge, ',');
            getline(donorData, donorZip, ',');
            getline(donorData, donorContact);

            // Check if the donor exists in the file by comparing each field
            if (donorName == name && donorBloodGroup == bloodGroup &&
                donorAge == to_string(age) && donorZip == to_string(zip) && donorContact == contact)
            {
                exists = true;
                break;
            }
        }
        file.close();
    }

    // If the donor doesn't exist, increment lastId and append to the file
    if (exists)
    {
        cout << "Donor already exists in the database. Not adding again.\n";
    }
    else
    {
        id = lastId + 1;  // Increment lastId for the new donor

        ofstream outFile(filename, ios::app);
        if (outFile.is_open())
        {
            outFile << id << "," << name << "," << bloodGroup << ","
                    << age << "," << zip << "," << contact << "\n";
            outFile.close();
            cout << "Donor information added successfully.\n";
        }
        else
        {
            cout << "Error opening file.\n";
        }
    }
}

// Getter for name
string Donor::getName() const
{
    return name;
}

// Getter for blood group
string Donor::getBloodGroup() const
{
    return bloodGroup;
}
