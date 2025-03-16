#include "../headers/bloodtest.h"



Bloodtest::Bloodtest(string bGroup, int qty,string hname)
    : bloodGroup(bGroup), quantity(qty),hospitalName(hname), isApproved(false) {}

bool Bloodtest::approveRequest() {
    if(isApproved)
        return true;
    else
        return false;
}

string Bloodtest::getBloodGroup() { return bloodGroup; }
int Bloodtest::getQuantity() { return quantity; }
bool Bloodtest::initial_test(){
    srand(time(0));
    cout << "Performing **Initial Blood Safety Tests** before adding to inventory...\n";

    bool bloodTyping = rand() % 10;       
    bool infectionScreening = rand() % 10; 
    bool hemoglobinLevel = rand() % 10;    

    if (bloodTyping){
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";
    }

    else{
        cout << "Blood Typing (ABO & Rh): ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        return false;
    } 
        

    if (infectionScreening){
        cout << "Infection Screening: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";

    }
    
    else {
        cout << "Infection Screening:  ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        return false;
    }
        

    if (hemoglobinLevel) {
        cout << "Hemoglobin Level: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Passed\n";
    }
    else{
        cout << "Hemoglobin Level: ";
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        return false;
    } 
        cout << "**All tests passed! Blood is safe for storage.**\n";
        return true;

}
