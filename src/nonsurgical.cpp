#include "../headers/nonsurgical.h"
#include <iostream>

NonSurgical::NonSurgical(string bGroup, int qty, string hName)
    : Bloodtest(bGroup, qty, hName) {}

void NonSurgical::request() {
    cout << "Non-Surgical blood request placed for " << quantity 
         << " units of " << bloodGroup << " by " << hospitalName << ".\n";
}

void NonSurgical::performTests() {
    srand(time(0));  
    cout << "Performing **basic compatibility and infection tests** for non-surgical request...\n";

    bool bloodTyping = rand() % 10;       
    bool iron = rand() % 10; 
    bool hemoglobinTest = rand() % 10;    

    if (bloodTyping){
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Passed\n";
    } 

    else {
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for non-surgical use.**\n";
        isApproved=false;
        return;
    }
        

    if (iron) {
        cout << "Ferritin Test: ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Passed\n";

    }
        
    else {
        cout << "Ferritin Test: ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for non-surgical use.**\n";
        isApproved=false;
        return;

    }
        

    if (hemoglobinTest) {
        cout << "Hemoglobin Test: ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Passed\n";
    }
        
    else {
        cout << "Hemoglobin Test: ";
        this_thread::sleep_for(chrono::seconds(3));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for non-surgical use.**\n";
        isApproved=false;
        return;
    }     
        cout << "**All tests passed! Blood is safe for non-surgical use.**\n";
        isApproved=true;
    

}
