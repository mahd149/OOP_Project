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
    if (bloodTyping){
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";
    } 
        
    else {
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for surgical use**\n";
        isApproved=false;
        return;
    }
        

    if (crossmatch){
        cout << "Crossmatching: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";
    }
        
    else{
        cout << "Crossmatching: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for surgical use**\n";
        isApproved=false;
        return;
    } 
        

    if (platelet) {
        cout << "Platelet Count: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";

    }
        
    else {
        cout << "Platelet Count: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for surgical use**\n";
        isApproved=false;
        return;

    }
        

    if (coagulationTest){
        cout << "Coagulation Test: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";

    } 
        
    else {
        cout << "Coagulation Test: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Test failed! Blood is NOT safe for surgical use**\n";
        isApproved=false;
        return;
    }
        cout << "**All tests passed! Blood can be used for surgery.**\n";
        isApproved=true;

}
