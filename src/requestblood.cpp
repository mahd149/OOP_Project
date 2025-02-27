#include "../headers/requestblood.h"

RequestBlood::RequestBlood(string bGroup, int qty, string hName)
    : bloodGroup(bGroup), quantity(qty), hospitalName(hName), isApproved(false) {}

bool RequestBlood::approveRequest() {
    if(isApproved)
        return true;
    else
        return false;
}

string RequestBlood::getBloodGroup() { return bloodGroup; }
int RequestBlood::getQuantity() { return quantity; }
string RequestBlood::getHospitalName() { return hospitalName; }
