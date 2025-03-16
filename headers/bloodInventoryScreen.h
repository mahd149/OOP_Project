#ifndef BLOOD_INVENTORY_SCREEN_H
#define BLOOD_INVENTORY_SCREEN_H

#include "screen.h"
#include "../headers/hospital.h"
#include <vector>
#include <string>

using namespace std;

class BloodInventoryScreen
{
private:
    Screen &currentScreen;
    vector<string> bloodInventory;
    Hospital &hospital;  

public:
    BloodInventoryScreen(Screen &screen, Hospital &hospital);  
    void update();
    void draw();
    void loadBloodInventory();
};

#endif
