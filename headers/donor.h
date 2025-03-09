#ifndef DONOR_H
#define DONOR_H

#include <string>
using namespace std;

class Donor
{
private:
    int id;
    string name;
    string bloodGroup;
    int age;
    int zip;
    string contact;

public:
    // Default constructor
    Donor();

    // Input donor information
    void inputDonor();

    // Save donor information to file
    void saveToFile(const string &filename);

    // Function to check if a string is a valid integer
    bool isValidInteger(const string &str);

    // Getter for name
    string getName() const;

    // Getter for blood group
    string getBloodGroup() const;
};

#endif // DONOR_H
