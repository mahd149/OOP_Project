#pragma once
#include "requestblood.h"

class Surgical : public RequestBlood {
public:
    Surgical(string bGroup, int qty, string hName);
    void request() override;
    void performTests() override;
};