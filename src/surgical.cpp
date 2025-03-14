#include "../headers/surgical.h"
#include <iostream>

Surgical::Surgical(string bGroup, int qty, string hName)
    : Bloodtest(bGroup, qty, hName) {}

void Surgical::request() {
    cout << "Surgical blood request placed for " << quantity 
         << " units of " << bloodGroup << " by " << hospitalName << ".\n";
}

void Surgical::performTests() {
    srand(time(0));  
    cout << "Performing **advanced compatibility and infection tests** for surgical request...\n";

    bool bloodTyping = rand() % 10;       
    bool crossmatch = rand() % 10;        
    bool platelet = rand() % 10; 
    bool coagulationTest = rand() % 10;   
    if (bloodTyping) 
        cout << "Blood Typing (ABO & Rh): Passed" << endl;
    else 
        cout << "Blood Typing (ABO & Rh): Failed" << endl;

    if (crossmatch) 
        cout << "Crossmatching: Passed" << endl;
    else 
        cout << "Crossmatching: Failed" << endl;

    if (platelet) 
        cout << "Platelet Count: Passed" << endl;
    else 
        cout << "Platelet Count: Failed" << endl;

    if (coagulationTest) 
        cout << "Coagulation Test: Passed" << endl;
    else 
        cout << "Coagulation Test: Failed" << endl;


    if (bloodTyping && crossmatch && platelet && coagulationTest) {
        cout << "**All tests passed! Blood can be used for surgery.**\n";
        isApproved=true;
    } else {
        cout << "**Test failed! Blood is NOT safe for surgical use.**\n";
        isApproved=false;
    }
}
