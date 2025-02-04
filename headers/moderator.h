//moderator.h


#pragma once

#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class Moderator: private User
{
    public:
    bool login(string, string) override;
    void openCSV_donor_info();
    
    
};
