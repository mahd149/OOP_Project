#include "../headers/nonsurgical.h"
#include <iostream>

NonSurgical::NonSurgical(string bGroup, int qty, string hName)
    : RequestBlood(bGroup, qty, hName) {}

void NonSurgical::request() {
    cout << "Non-Surgical blood request placed for " << quantity 
         << " units of " << bloodGroup << " by " << hospitalName << ".\n";
}

void NonSurgical::performTests() {
    srand(time(0));  
    cout << "Performing **basic compatibility and infection tests** for non-surgical request...\n";

    bool bloodTyping = rand() % 10;       
    bool infectionScreening = rand() % 10; 
    bool hemoglobinTest = rand() % 10;    

    if (bloodTyping) 
        cout << "Blood Typing (ABO & Rh): Passed" << endl;
    else 
        cout << "Blood Typing (ABO & Rh): Failed" << endl;

    if (infectionScreening) 
        cout << "Infection Screening: Passed" << endl;
    else 
        cout << "Infection Screening: Failed" << endl;

    if (hemoglobinTest) 
        cout << "Hemoglobin Test: Passed" << endl;
    else 
        cout << "Hemoglobin Test: Failed" << endl;

    if (bloodTyping && infectionScreening && hemoglobinTest) {
        cout << "**All tests passed! Blood is safe for non-surgical use.**\n";
        isApproved=true;
    } else {
        cout << "**Test failed! Blood is NOT safe for non-surgical use.**\n";
        isApproved=false;
    }
}
