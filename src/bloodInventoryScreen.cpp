#include "../headers/bloodInventoryScreen.h"
#include "../headers/hospital.h"
#include "raylib.h"

BloodInventoryScreen::BloodInventoryScreen(Screen &screen, Hospital &hospital)
    : currentScreen(screen), hospital(hospital) 
{
    loadBloodInventory();
}



void BloodInventoryScreen::loadBloodInventory()
{
    bloodInventory = hospital.readBloodInventory();
}

void BloodInventoryScreen::update()
{
    if (IsKeyPressed(KEY_ZERO))
    {
        currentScreen = POST_HOSPITAL_SCREEN;
    }
}

void BloodInventoryScreen::draw()
{
    ClearBackground(RAYWHITE);
    DrawText("Blood Inventory", 50, 30, 30, DARKGRAY);

    int yOffset = 80;
    for (const auto &entry : bloodInventory)
    {
        DrawText(entry.c_str(), 50, yOffset, 20, BLACK);
        yOffset += 30;
    }

    DrawRectangle(50, 500, 300, 40, DARKGRAY);
    DrawText("0. Back to Hospital Menu", 60, 510, 20, WHITE);
}
