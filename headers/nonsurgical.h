#pragma once
#include "requestblood.h"

class NonSurgical : public RequestBlood {
public:
    NonSurgical(string bGroup, int qty, string hName);
    void request() override;
    void performTests() override;
};
