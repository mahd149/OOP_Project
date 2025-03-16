// hospital.h

// private inheritance from user class
// give acces to hospital bloodbank files and
// search for donors when needed
#pragma once
#include "user.h"
#include "donor.h"
#include <unordered_map>
#include <vector>
#include <ctime>

using namespace std;

class Hospital
{
private:
    time_t lastDonationTime;
    time_t currentTime;
    bool donorFound;

protected:
    static int lastId;      // A single copy of lastId exists for the whole class, not for each object.
    //                      Changing lastId in one object changes it for all objects.
    vector<string> bloodTypingResult;
    vector<string> infectionScreeningResults;
    vector<string> hemoglobinLevelResults;

public:
    /*  bool login(string, string) override; */
    // void openCSV_blood_inventory_info();
    vector<string> readBloodInventory();
    vector<string> addBlood(int donorId);
    string normalizeBloodGroup(string bg);
    bool bloodyTester(string bloodGroup, int amount);
    // void removeBlood(const string &bloodGroup, int amount);
    // string trim(const string &str);
    // void searchBlood()
    vector<string> bloodyTimeTracker();
    void write_to_inventory(int amount, string bloodgroup);
    void write_details(int amount, Donor d, vector<string> donorRecords);
    void write_details(int amount, Donor d, vector<string> donorRecords, int donorID); //update // polymorphism
    
    
    static int getLastId() { return lastId; }
    ~Hospital() {}
};
