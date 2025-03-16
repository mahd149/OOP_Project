#include "../headers/searchScreen.h"
#include "../headers/menu.h"
#include "raylib.h"
#include <iostream>
#include <thread>

using namespace std;

SearchScreen::SearchScreen(Screen &screen)
    : searchInProgress(false), bloodGroupInput(""), zipInput(""), currentScreen(screen), currentFocus(BLOOD_GROUP_INPUT), clearinput(false) {}

void SearchScreen::update()
{
    handleInput();

    if (IsKeyPressed(KEY_ENTER) && !searchInProgress)
    {
        if (currentFocus == BLOOD_GROUP_INPUT && !bloodGroupInput.empty())
        {
            currentFocus = ZIP_CODE_INPUT;
        }
        else if (currentFocus == ZIP_CODE_INPUT && !zipInput.empty())
        {
            searchInProgress = true;
            thread searchThread(&SearchScreen::searchForBlood, this);
            clearinput = true;
            searchThread.detach();
        }
    }
}

void SearchScreen::draw()
{
    // Draw Blood Group input label and field
    DrawText("Enter Blood Group:", 50, 50, 20, BLACK);
    DrawRectangle(250, 45, 150, 30, LIGHTGRAY);
    DrawText(bloodGroupInput.c_str(), 260, 50, 20, BLACK);

    // Draw ZIP Code input label and field
    DrawText("Enter ZIP Code:", 50, 120, 20, BLACK);
    DrawRectangle(250, 115, 150, 30, LIGHTGRAY);
    DrawText(zipInput.c_str(), 260, 120, 20, BLACK);

    // Display search results
    int yOffset = 200;
    if (!searchInProgress)
    {
        if (clearinput)
        {
            currentFocus = BLOOD_GROUP_INPUT;
            bloodGroupInput.clear();
            zipInput.clear();
            clearinput = false;
        }
        else
        {
            for (const auto &result : searchResults)
            {
                if (result == "No donors found.")
                {
                    DrawText(result.c_str(), 50, yOffset, 20, RED);
                    break;
                }
                else
                    DrawText(result.c_str(), 50, yOffset, 20, DARKGRAY);
                yOffset += 25;
            }
        }
    }

    // Back button to return to the main menu
    DrawRectangle(50, 500, 100, 40, LIGHTGRAY);
    DrawText("Back", 70, 510, 20, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX >= 50 && mouseY >= 500 && mouseX <= 150 && mouseY <= 540)
        {
            bloodGroupInput.clear();
            zipInput.clear();
            currentFocus = BLOOD_GROUP_INPUT;
            currentScreen = MAIN_MENU;
            searchResults.clear();
            clearinput = true;
        }
    }
}

void SearchScreen::handleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (currentFocus == BLOOD_GROUP_INPUT && !bloodGroupInput.empty())
        {
            bloodGroupInput.pop_back();
        }
        else if (currentFocus == ZIP_CODE_INPUT && !zipInput.empty())
        {
            zipInput.pop_back();
        }
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if (currentFocus == BLOOD_GROUP_INPUT && bloodGroupInput.size() < 5)
        {
            bloodGroupInput += (char)key;
        }
        else if (currentFocus == ZIP_CODE_INPUT && zipInput.size() < 5)
        {
            zipInput += (char)key;
        }
        key = GetCharPressed();
    }
}

void SearchScreen::searchForBlood()
{
    searchResults.clear();
    search.searchBlood(bloodGroupInput, zipInput, searchResults);
    searchInProgress = false;
}
