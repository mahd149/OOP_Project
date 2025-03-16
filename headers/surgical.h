#pragma once
#include "bloodtest.h"
#include <vector>

class Surgical : public Bloodtest{
public:
    vector<string> bloodTypingString;
    vector<string> crossMatchString;
    vector<string> plateletString;
    vector<string> coagulationString;
    bool isApproved;
    Surgical(string bGroup, int qty, string hName);
    void request() override;
    void performTests() override;
};