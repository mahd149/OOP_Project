#pragma once
#include "bloodtest.h"

class NonSurgical : public Bloodtest {
public:
    NonSurgical(string bGroup, int qty, string hName);
    void request() override;
    void performTests() override;
};
