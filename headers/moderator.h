//moderator.h


#pragma once

#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class Moderator: private User
{
    public:
    //constructor
    bool login(string, string) override;
    void openCSV_donor_info();
    //add functions for opening othercsv files
    //excluding admin files and hospital bank data
    
};
