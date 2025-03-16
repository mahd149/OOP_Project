#include "../headers/moderatorScreen.h"
#include "../headers/menu.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ModeratorScreen::ModeratorScreen(Screen &screen)
    : emailInput(""), passwordInput(""), loginInProgress(false), loginSuccess(false), currentScreen(screen), invalidLoginUpdater(false) {}

void ModeratorScreen::update()
{
    handleInput();

    if (IsKeyPressed(KEY_ENTER))
    {
        if (currentFocus == MODERATOR_EMAIL_INPUT && !emailInput.empty())
        {
            currentFocus = MODERATOR_PASSWORD_INPUT;
        }
        else if (currentFocus == MODERATOR_PASSWORD_INPUT && !passwordInput.empty())
        {
            loginInProgress = true;
            loginSuccess = login(emailInput, passwordInput); // Validate credentials from CSV
            loginSuccessChecker();
            loginInProgress = false;
        }
    }
}

void ModeratorScreen::draw()
{
    ClearBackground(RAYWHITE);

    DrawText("Enter Email:", 50, 50, 20, BLACK);
    DrawRectangle(250, 45, 300, 30, LIGHTGRAY);
    DrawText(emailInput.c_str(), 260, 50, 20, BLACK);

    DrawText("Enter Password:", 50, 120, 20, BLACK);
    DrawRectangle(250, 115, 300, 30, LIGHTGRAY);
    DrawText(passwordInput.c_str(), 260, 120, 20, BLACK);

    if (loginInProgress)
    {
        DrawText("Logging in...", 50, 170, 20, DARKGRAY);
    }
    else if (loginSuccess)
    {
        DrawText("Login successful!", 50, 170, 20, GREEN);
    }
    else if (invalidLoginUpdater)
    {
        DrawText("Invalid Username or Password", 50, 170, 20, RED);
    }

    DrawRectangle(50, 500, 100, 40, LIGHTGRAY);
    DrawText("Back", 70, 510, 20, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX >= 50 && mouseY >= 500 && mouseX <= 150 && mouseY <= 540)
        {
            currentScreen = MAIN_MENU;
            passwordInput.clear();
            emailInput.clear();
            currentFocus = MODERATOR_EMAIL_INPUT;
        }
    }
}

void ModeratorScreen::handleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (currentFocus == MODERATOR_EMAIL_INPUT && !emailInput.empty())
        {
            emailInput.pop_back();
        }
        else if (currentFocus == MODERATOR_PASSWORD_INPUT && !passwordInput.empty())
        {
            passwordInput.pop_back();
        }
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if (currentFocus == MODERATOR_EMAIL_INPUT && emailInput.size() < 30)
        {
            emailInput += (char)key;
        }
        else if (currentFocus == MODERATOR_PASSWORD_INPUT && passwordInput.size() < 20)
        {
            passwordInput += (char)key;
        }
        key = GetCharPressed();
    }
}

bool ModeratorScreen::login(const string &inputEmail, const string &inputPassword)
{
    ifstream file("CSV_Files/moderator_data.csv");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open moderator data file!" << endl;
        return false;
    }

    string line, stored_username, stored_email, stored_password;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');

        if (stored_email == inputEmail && stored_password == inputPassword)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void ModeratorScreen::loginSuccessChecker()
{
    if (!loginSuccess)
    {
        emailInput.clear();
        passwordInput.clear();
        currentFocus = MODERATOR_EMAIL_INPUT;
        invalidLoginUpdater = true;
    }
    else //successfull login // newpage
    {
        emailInput.clear();
        passwordInput.clear();
        currentFocus = MODERATOR_EMAIL_INPUT;
        invalidLoginUpdater = false;
        currentScreen = POST_MODERATOR_SCREEN;
    }
}
