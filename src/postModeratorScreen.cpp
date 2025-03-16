#include "../headers/postModeratorScreen.h"
#include "../headers/fileOptionsScreen.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>

using namespace std;

PostModeratorScreen::PostModeratorScreen(Screen &screen)
    : currentScreen(screen) {}

void PostModeratorScreen::update()
{

    if (IsKeyPressed(KEY_ONE))
    {

        cout << "Opening Donor Files..." << endl;
        openCSVFile("CSV_Files/donor_info.csv");
    }
    else if (IsKeyPressed(KEY_TWO))
    {

        cout << "Opening Blood Inventory Files..." << endl;
        openCSVFile("CSV_Files/blood_inventory.csv");
    }
    else if (IsKeyPressed(KEY_ZERO))
    {

        currentScreen = MAIN_MENU;
    }
}

void PostModeratorScreen::draw()
{
    ClearBackground(RAYWHITE);

   
    /* DrawRectangle(50, 115, 400, 40, LIGHTGRAY);         
    DrawText("1. Open Donor Files", 60, 120, 30, BLACK); 

    DrawRectangle(50, 155, 400, 40, LIGHTGRAY);                   
    DrawText("2. Open Blood Inventory Files", 60, 160, 30, BLACK); 

    DrawRectangle(50, 195, 400, 40, DARKGRAY);            
    DrawText("0. Back to Main Menu", 60, 200, 30, WHITE); */

    DrawText("Moderator Options:", 50, 50, 20, BLACK);

    DrawRectangle(50, 100, 400, 40, LIGHTGRAY);
    DrawText("1. Open Donor Files", 70, 110, 20, BLACK);

    DrawRectangle(50, 150, 400, 40, LIGHTGRAY);
    DrawText("2. Open Blood Inventory Files", 70, 160, 20, BLACK);

    DrawRectangle(100, 200, 400, 40, DARKGRAY);
    DrawText("0. Back to Main Menu", 120, 210, 20, WHITE);

    
}
