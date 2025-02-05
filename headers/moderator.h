//moderator.h


#pragma once

#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class Moderator: public User
{
    public:
    //constructor
    Moderator(string u_name = "Unknown", string u_email = "", string pass = "");
    bool login(string, string) override;
    void openCSV_donor_info();
    void openCSV_bloodBank_info();
    //add functions for opening othercsv files
    //excluding admin files and hospital bank data

    ~Moderator() {}
    
};
