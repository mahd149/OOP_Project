#pragma once
#include <string>
#include<ctime>
#include<iostream>

using namespace std;

class Bloodtest {
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

    virtual ~Bloodtest() {}
};
