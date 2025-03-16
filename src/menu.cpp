#include "../headers/menu.h"
#include "raylib.h"

// Constructor
MainMenu::MainMenu()
{
    bgImage = LoadTexture("assets/background.png");
    buttons[0] = {300, 200, 250, 50};
    buttons[1] = {300, 260, 250, 50};
    buttons[2] = {300, 320, 250, 50};
    buttons[3] = {300, 380, 250, 50};
    buttons[4] = {300, 440, 250, 50};

    labels[0] = "Search for Blood";
    labels[1] = "Admin Login";
    labels[2] = "Moderator Login";
    labels[3] = "Hospital Login";
    labels[4] = "Exit";
    
    for (int i = 0; i < 5; i++)
    {
        hovered[i] = false;
    }
}

// Destructor
MainMenu::~MainMenu()
{
    UnloadTexture(bgImage);
}

// Draw Menu
void MainMenu::drawMenu(bool isMainMenu)
{
    if (isMainMenu) {
        DrawTexture(bgImage, 0, 0, WHITE);  // Only draw background in MAIN_MENU screen
        DrawText("Blood Bank Management System", 270, 150, 20, BLACK);

        for (int i = 0; i < 5; i++)
        {
            Color btnColor = hovered[i] ? (Color){100, 100, 255, 255} : (Color){50, 50, 200, 255}; // if hovered light blue, otherwise default
            DrawRectangleGradientV(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, btnColor, BLUE);
            DrawRectangleLinesEx(buttons[i], 3, WHITE); // border
            DrawText(labels[i], buttons[i].x + 20, buttons[i].y + 15, 20, WHITE);
        }
        EndDrawing();
    }
}

// Handle Button Click
MenuOption MainMenu::handleButtonClick(int mouseX, int mouseY)
{
    for (int i = 0; i < 5; i++)
    {
        hovered[i] = CheckCollisionPointRec(Vector2{(float)mouseX, (float)mouseY}, buttons[i]);
        if (hovered[i] && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return static_cast<MenuOption>(i);
        }
    }
    return NONE;
}
