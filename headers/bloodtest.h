#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

class Bloodtest
{
private:
    vector<string> bloodTypingString;
    vector<string> infectionScreeningString;
    vector<string> hemoglobinLevelString;

protected:
    string bloodGroup;
    int quantity;
    string hospitalName;
    bool isApproved;

public:
    Bloodtest(string bGroup, int qty, string hName);
    virtual void request() = 0;
    virtual void performTests() = 0;
    bool approveRequest();
    bool initial_test();

    string getBloodGroup();
    int getQuantity();
    string getHospitalName();
    vector<string> getBloodTypingResults() const;
    vector<string> getInfectionScreeningResults() const;
    vector<string> getHemoglobinLevelResults() const;

    virtual ~Bloodtest() {}
};
