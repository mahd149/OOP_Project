// admin.h

#pragma once

// #include <iostream>
// #include <string>
#include "user.h"

using namespace std;

class Admin : public User
{
public:
    Admin(string u_name = "Unknown", string u_email = "", string pass = "");
   

    // need constructor
    bool login(string, string) override;
    void openCSV(const string &filename);
    void Register_Admin(string, string, string);
    void Register_Moderator(string, string, string);
    ~Admin() { }
};
