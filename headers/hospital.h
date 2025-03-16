//hospital.h


//private inheritance from user class
//give acces to hospital bloodbank files and 
//search for donors when needed
#pragma once
#include "user.h"
#include "surgical.h"
#include "nonsurgical.h"
#include "donor.h"
#include <unordered_map>
#include <vector>

using namespace std;



class Hospital: public User{
    public: 
        bool login(string, string) override;
        // void openCSV_blood_inventory_info();
        void readBloodInventory();
        void addDonor(Donor &newDonor);
        
        void addBlood(int donorId);
        void removeBlood(const string &bloodGroup, int amount);
        unordered_map<string, int> checkExpiry(int minutes);


        string trim(const string &str);
        void searchBlood();
        
        void requestBlood(const string &bloodGroup, int amount, bool isSurgical);
        void processBloodRequest(Bloodtest *request);
        void write_to_inventory(int amount,string bloodgroup);
        void write_details(int amount,Donor d,time_t currentTime,vector<string>donorRecords);
        string normalizeBloodGroup(string bg);
        ~Hospital(){}

};
