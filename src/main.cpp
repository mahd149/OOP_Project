#include "../headers/search.h"
#include "../headers/screen.h"
#include "../headers/searchScreen.h"
#include "../headers/menu.h"
#include "../headers/adminScreen.h"
#include "../headers/postLoginScreen.h"
#include "../headers/adminRegistrationScreen.h"
#include "../headers/moderatorRegistrationScreen.h"
#include "../headers/fileOptionsScreen.h"
#include "../headers/moderatorScreen.h"
#include "../headers/postModeratorScreen.h"
#include "../headers/hospitalScreen.h"
#include "../headers/postHospitalScreen.h"
#include "../headers/bloodInventoryScreen.h"
#include "../headers/hospital.h"
#include "../headers/addBloodScreen.h"

#include "raylib.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

//Global Object
Search search;
Hospital hospital;

/// @instance ////////////////
Screen currentScreen = MAIN_MENU;
SearchScreen searchScreen(currentScreen);
AdminScreen adminScreen(currentScreen);
PostLoginScreen postLoginScreen(currentScreen);
AdminRegistrationScreen adminRegistrationScreen(currentScreen);
ModeratorRegistrationScreen moderatorRegistrationScreen(currentScreen);
FileOptionsScreen fileOptionsScreen(currentScreen);
ModeratorScreen moderatorScreen(currentScreen);
PostModeratorScreen postModeratorScreen(currentScreen);
HospitalScreen hospitalScreen(currentScreen);
PostHospitalScreen postHospitalScreen(currentScreen);
BloodInventoryScreen bloodInventoryScreen(currentScreen, hospital);
AddBloodScreen addBloodScreen(currentScreen, hospital);
//////////////////////////////////

bool searchInProgress = false;
vector<string> searchResults;
string bloodGroupInput = "";
string zipInput = "";

int main()
{
    InitWindow(800, 600, "Blood Bank Management");
    SetTargetFPS(60);

    MainMenu mainMenu;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == MAIN_MENU)
        {
            mainMenu.drawMenu(true);
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            MenuOption choice = mainMenu.handleButtonClick(mouseX, mouseY);

            if (choice == SEARCH_BLOOD && !searchInProgress)
            {
                currentScreen = SEARCH_SCREEN;
            }
            else if (choice == ADMIN_LOGIN && !searchInProgress)
            {
                currentScreen = ADMIN_LOGIN_SCREEN;
            }
            else if (choice == MODERATOR_LOGIN && !searchInProgress)
            {
                currentScreen = MODERATOR_LOGIN_SCREEN;
            }
            else if (choice == HOSPITAL_LOGIN && !searchInProgress)
            {
                currentScreen = HOSPITAL_LOGIN_SCREEN;
            }
            else if (choice == EXIT)
            {
                break;
            }
        }
        else if (currentScreen == SEARCH_SCREEN)
        {
            EndDrawing();
            searchScreen.update();
            searchScreen.draw();
        }
        else if (currentScreen == ADMIN_LOGIN_SCREEN)
        {
            EndDrawing();
            adminScreen.update();
            adminScreen.draw();
        }
        else if (currentScreen == POST_LOGIN_SCREEN)
        {
            EndDrawing();
            postLoginScreen.update();
            postLoginScreen.draw();
        }
        else if (currentScreen == ADMIN_REGISTRATION_SCREEN)
        {
            EndDrawing();
            adminRegistrationScreen.update();
            adminRegistrationScreen.draw();
        }
        else if (currentScreen == MODERATOR_REGISTRATION_SCREEN)
        {
            EndDrawing();
            moderatorRegistrationScreen.update();
            moderatorRegistrationScreen.draw();
        }
        else if (currentScreen == FILE_OPTIONS_SCREEN)
        {
            EndDrawing();
            fileOptionsScreen.update();
            fileOptionsScreen.draw();
        }
        else if (currentScreen == MODERATOR_LOGIN_SCREEN)
        {
            EndDrawing();
            moderatorScreen.update();
            moderatorScreen.draw();
        }
        else if (currentScreen == POST_MODERATOR_SCREEN) 
        {
            EndDrawing();
            postModeratorScreen.update();
            postModeratorScreen.draw();
        }
        else if (currentScreen == HOSPITAL_LOGIN_SCREEN)
        {
            EndDrawing();
            hospitalScreen.update();
            hospitalScreen.draw();
        }
        else if (currentScreen == POST_HOSPITAL_SCREEN)
        {
            EndDrawing();
            postHospitalScreen.update();
            postHospitalScreen.draw();
        }
        else if (currentScreen == BLOOD_INVENTORY_SCREEN)
        {
            EndDrawing();
            bloodInventoryScreen.update();
            bloodInventoryScreen.draw();
        }
        else if (currentScreen == ADD_BLOOD_SCREEN)
        {
            EndDrawing();
            addBloodScreen.update();
            addBloodScreen.draw();
        }
    }

    CloseWindow();
    return 0;
}
