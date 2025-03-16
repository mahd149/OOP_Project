#include "../headers/postHospitalScreen.h"
#include "../headers/menu.h"
#include "raylib.h"
#include <iostream>

using namespace std;

PostHospitalScreen::PostHospitalScreen(Screen &screen) : currentScreen(screen) {}

void PostHospitalScreen::update()
{
    if (IsKeyPressed(KEY_ONE))
    {
        currentScreen = BLOOD_INVENTORY_SCREEN;
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        currentScreen = ADD_BLOOD_SCREEN;
    }
    else if (IsKeyPressed(KEY_THREE))
    {
        // TODO: Navigate to Check Expiry screen
    }
    else if (IsKeyPressed(KEY_FOUR))
    {
        // TODO: Navigate to Request Blood screen
    }
    else if (IsKeyPressed(KEY_FIVE))
    {
        // TODO: Navigate to Search Blood screen
    }
    else if (IsKeyPressed(KEY_SIX))
    {
        // TODO: Navigate to Add Donor screen
    }
    else if (IsKeyPressed(KEY_ZERO))
    {
        currentScreen = MAIN_MENU;
    }
}

void PostHospitalScreen::draw()
{
    ClearBackground(RAYWHITE);

    DrawText("Hospital Dashboard", 50, 30, 30, DARKGRAY);

    DrawRectangle(50, 80, 400, 40, LIGHTGRAY);
    DrawText("1. Read Blood Inventory", 60, 90, 24, BLACK);

    DrawRectangle(50, 130, 400, 40, LIGHTGRAY);
    DrawText("2. Add Blood", 60, 140, 24, BLACK);

    DrawRectangle(50, 180, 400, 40, LIGHTGRAY);
    DrawText("3. Check Expiry", 60, 190, 24, BLACK);

    DrawRectangle(50, 230, 400, 40, LIGHTGRAY);
    DrawText("4. Request Blood", 60, 240, 24, BLACK);

    DrawRectangle(50, 280, 400, 40, LIGHTGRAY);
    DrawText("5. Search Blood", 60, 290, 24, BLACK);

    DrawRectangle(50, 330, 400, 40, LIGHTGRAY);
    DrawText("6. Add Donor", 60, 340, 24, BLACK);

    DrawRectangle(50, 380, 400, 40, DARKGRAY);
    DrawText("0. Back to Main Menu", 60, 390, 24, WHITE);
}
