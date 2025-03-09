//hospital.h


//private inheritance from user class
//give acces to hospital bloodbank files and 
//search for donors when needed
#pragma once
#include "user.h"
#include "surgical.h"
#include "nonsurgical.h"

using namespace std;



class Hospital: public User{
    public: 
        bool login(string, string) override;
        // void openCSV_blood_inventory_info();
        void readBloodInventory();
        void addBlood(const string &bloodGroup, int amount);
        void removeBlood(const string &bloodGroup, int amount);

        string trim(const string &str);
        void searchBlood();
        
        void requestBlood(const string &bloodGroup, int amount, bool isSurgical);
        void processBloodRequest(RequestBlood *request);
        ~Hospital(){}

};
