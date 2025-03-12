#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <map>
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

    Donor(int a, string n, string s, int b, int z,string c);

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

    int getAge() const;

    int getZip() const;

    string getContact() const; 
    
    int getId() const;

    bool login(string name, string num);

    void showStatistics();
};


#endif // DONOR_H
