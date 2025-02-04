// admin.h

#pragma once

#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class Admin: private User
{
    public:
    bool login(string, string) override;
    void openCSV(const string& filename);
    void Register(string, string, string);
};
