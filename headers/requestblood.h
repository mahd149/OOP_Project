#pragma once
#include <string>

using namespace std;

class RequestBlood {
protected:
    string bloodGroup;
    int quantity;
    string hospitalName;
    bool isApproved;  

public:
    RequestBlood(string bGroup, int qty, string hName);
    virtual void request() = 0; 
    virtual void performTests() = 0;
    bool approveRequest(); 

    string getBloodGroup();
    int getQuantity();
    string getHospitalName();

    virtual ~RequestBlood() {}
};
