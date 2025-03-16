#include "../headers/fileOptionsScreen.h"
#include "../headers/menu.h"
#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

void openCSVFile(const string &filePath)
{
    string command = "start " + filePath;
    int result = system(command.c_str());
    if (result != 0)
    {
        cerr << "Error: Unable to open file " << filePath << endl;
    }
}

FileOptionsScreen::FileOptionsScreen(Screen &screen)
    : currentScreen(screen), selectedOption(-1) {}

void FileOptionsScreen::update()
{
    handleInput();
}

void FileOptionsScreen::draw()
{
    ClearBackground(RAYWHITE);

    DrawText("File Options", 50, 50, 30, BLACK);

    // Define button positions and sizes
    int startX = 40, startY = 110, width = 400, height = 40, spacing = 50;
    Color buttonColor = LIGHTGRAY;
    Color textColor = BLACK;

    // Draw bounding rectangles with text inside
    DrawRectangle(startX, startY, width, height, buttonColor);
    DrawText("1. Open Admin Info File", startX + 10, startY + 10, 20, textColor);

    DrawRectangle(startX, startY + spacing, width, height, buttonColor);
    DrawText("2. Open Moderator File", startX + 10, startY + spacing + 10, 20, textColor);

    DrawRectangle(startX, startY + spacing * 2, width, height, buttonColor);
    DrawText("3. Open Donor File", startX + 10, startY + spacing * 2 + 10, 20, textColor);

    DrawRectangle(startX, startY + spacing * 3, width, height, buttonColor);
    DrawText("4. Open Blood Inventory File", startX + 10, startY + spacing * 3 + 10, 20, textColor);

    DrawRectangle(startX, startY + spacing * 4, width, height, buttonColor);
    DrawText("5. Open Hospital File", startX + 10, startY + spacing * 4 + 10, 20, textColor);

    // Draw back option
    int backX = startX + 60;          // Shift right
    int backY = startY + spacing * 5; // Shift lower
    DrawRectangle(backX, backY, width, height, DARKGRAY);
    DrawText("0. Back to Post Login Screen", backX + 10, backY + 10, 20, RAYWHITE);
}

void FileOptionsScreen::handleInput()
{
    if (IsKeyPressed(KEY_ONE))
    {
        selectedOption = 1;
        openCSVFile("CSV_Files/admin_data.csv");
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        selectedOption = 2;
        openCSVFile("CSV_Files/moderator_data.csv");
    }
    else if (IsKeyPressed(KEY_THREE))
    {
        selectedOption = 3;
        openCSVFile("CSV_Files/donor_info.csv");
    }
    else if (IsKeyPressed(KEY_FOUR))
    {
        selectedOption = 4;
        openCSVFile("CSV_Files/blood_inventory.csv");
    }
    else if (IsKeyPressed(KEY_FIVE))
    {
        selectedOption = 5;
        openCSVFile("CSV_Files/hospital_info.csv");
    }
    else if (IsKeyPressed(KEY_ZERO))
    {
        currentScreen = POST_LOGIN_SCREEN;
    }
}
