#pragma once
#include "bloodtest.h"

class Surgical : public Bloodtest{
public:
    Surgical(string bGroup, int qty, string hName);
    void request() override;
    void performTests() override;
};