#include "../headers/donor.h"
#include "../headers/hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>

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
Donor::Donor(int a, string n, string s, int b, int z,string c):id(a),name(n),bloodGroup(s),age(b),zip(z),contact(c){}

string normalizeBloodGroup2(string bg)
{
    transform(bg.begin(), bg.end(), bg.begin(), ::toupper);
    if (bg == "A+" || bg == "A-" || bg == "B+" || bg == "B-" ||
        bg == "AB+" || bg == "AB-" || bg == "O+" || bg == "O-")
    {
        return bg;
    }
    return "";
}

void Donor::inputDonor()
{
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    while (true)
    {
        cout << "Enter Blood Group: ";
        cin >> bloodGroup;
        bloodGroup = normalizeBloodGroup2(bloodGroup);
        if (!bloodGroup.empty())
            break;
        cout << "Invalid blood group entered. Please enter a valid blood group (A+, A-, B+, B-, AB+, AB-, O+, O-).\n";
    }

    while (true)
    {
        cout << "Enter Age (18-150): ";
        string ageInput;
        cin >> ageInput;
        if (isValidInteger(ageInput))
        {
            age = stoi(ageInput);
            if (age >= 18 && age <= 150)
                break;
        }
        cout << "Invalid age. Please enter a valid number between 18 and 150.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Enter Zip Code (1-9999): ";
        string zipInput;
        cin >> zipInput;
        if (isValidInteger(zipInput))
        {
            zip = stoi(zipInput);
            if (zip >= 1 && zip <= 9999)
                break;
        }
        cout << "Invalid zip code. Please enter a valid number between 1 and 9999.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Enter Contact Number (11-digit integer): ";
        cin >> contact;
        if (isValidInteger(contact) && contact.length() == 11)
            break;
        cout << "Invalid contact number. Please enter exactly 11 digits.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool Donor::isValidInteger(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return !str.empty();
}

void Donor::saveToFile(const string &filename)
{
    ifstream file(filename);
    string line;
    int lastId = 0;
    bool exists = false;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string temp, donorName, donorBloodGroup, donorAge, donorZip, donorContact;
            int currentId;

            getline(ss, temp, ',');
            try
            {
                currentId = stoi(temp);
            }
            catch (...)
            {
                continue;
            }
            lastId = currentId;

            getline(ss, donorName, ',');
            getline(ss, donorBloodGroup, ',');
            getline(ss, donorAge, ',');
            getline(ss, donorZip, ',');
            getline(ss, donorContact);

            if (donorName == name && donorBloodGroup == bloodGroup &&
                donorAge == to_string(age) && donorZip == to_string(zip) && donorContact == contact)
            {
                exists = true;
                break;
            }
        }
        file.close();
    }

    if (exists)
    {
        cout << "Donor already exists in the database. Not adding again.\n";
    }
    else
    {
        id = lastId + 1;
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

string Donor::getName() const
{
    return name;
}

string Donor::getBloodGroup() const
{
    return bloodGroup;
}

int Donor::getZip() const
{
    return zip;
}

int Donor::getAge() const
{
    return age;
}

string Donor::getContact() const
{
    return contact;
}
int Donor::getId() const{
    return id;
}
