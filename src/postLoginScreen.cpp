#include "../headers/postLoginScreen.h"
#include "../headers/menu.h"
#include "raylib.h"
#include <iostream>

using namespace std;

PostLoginScreen::PostLoginScreen(Screen &screen)
    : currentScreen(screen) {}

void PostLoginScreen::update()
{
    handleInput();
}

void PostLoginScreen::draw()
{
    ClearBackground(RAYWHITE);

    DrawText("Admin Options:", 50, 50, 20, BLACK);

    DrawRectangle(50, 100, 300, 40, LIGHTGRAY);
    DrawText("1. Open Files", 70, 110, 20, BLACK);

    DrawRectangle(50, 150, 300, 40, LIGHTGRAY);
    DrawText("2. Register Admin", 70, 160, 20, BLACK);

    DrawRectangle(50, 200, 300, 40, LIGHTGRAY);
    DrawText("3. Register Moderator", 70, 210, 20, BLACK);

    DrawRectangle(50, 250, 300, 40, LIGHTGRAY);
    DrawText("0. Back to Main Menu", 70, 260, 20, BLACK);
}

void PostLoginScreen::handleInput()
{

    if (IsKeyPressed(KEY_ONE))
    {
        currentScreen = FILE_OPTIONS_SCREEN;
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        currentScreen = ADMIN_REGISTRATION_SCREEN;
    }
    else if (IsKeyPressed(KEY_THREE))
    {
        currentScreen = MODERATOR_REGISTRATION_SCREEN;
    }
    else if (IsKeyPressed(KEY_ZERO))
    {
        currentScreen = MAIN_MENU; 
    }
}
