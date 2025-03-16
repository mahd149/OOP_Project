#include "../headers/surgical.h"
#include <iostream>

Surgical::Surgical(string bGroup, int qty, string hName)
    : Bloodtest(bGroup, qty, hName) {}

void Surgical::request()
{
    cout << "Surgical blood request placed for " << quantity
         << " units of " << bloodGroup << " by " << hospitalName << ".\n";
}

void Surgical::performTests()
{
    srand(time(0));
    cout << "Performing **advanced compatibility and infection tests** for surgical request...\n";

    bool bloodTyping = rand() % 10;
    bool crossmatch = rand() % 10;
    bool platelet = rand() % 10;
    bool coagulationTest = rand() % 10;
    if (bloodTyping)
    {
        cout << "Blood Typing (ABO & Rh): Passed" << endl;
        bloodTypingString.push_back("Blood Typing (ABO & Rh): Passed");
    }
    else
    {
        cout << "Blood Typing (ABO & Rh): Failed" << endl;
        bloodTypingString.push_back("Blood Typing (ABO & Rh): Failed");
    }

    if (crossmatch)
    {
        cout << "Crossmatching: Passed" << endl;
        crossMatchString.push_back("Crossmatching: Passed");
    }
    else
    {
        cout << "Crossmatching: Failed" << endl;
        crossMatchString.push_back("Crossmatching: Failed");
    }

    if (platelet)
    {
        cout << "Platelet Count: Passed" << endl;
        plateletString.push_back("Platelet Count: Passed");
    }
    else
    {
        cout << "Platelet Count: Failed" << endl;
        plateletString.push_back("Platelet Count: Passed");
    }

    if (coagulationTest)
    {
        cout << "Coagulation Test: Passed" << endl;
        coagulationString.push_back("Coagulation Test: Passed");
    }
    else
    {
        cout << "Coagulation Test: Failed" << endl;
        coagulationString.push_back("Coagulation Test: Failed");
    }

    if (bloodTyping && crossmatch && platelet && coagulationTest)
    {
        cout << "**All tests passed! Blood can be used for surgery.**\n";
        isApproved = true;
    }
    else
    {
        cout << "**Test failed! Blood is NOT safe for surgical use.**\n";
        isApproved = false;
    }
}
