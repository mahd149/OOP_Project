#include "../headers/hospitalScreen.h"
#include "../headers/menu.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

HospitalScreen::HospitalScreen(Screen &screen)
    : emailInput(""), passwordInput(""), loginInProgress(false), loginSuccess(false), currentScreen(screen), invalidLoginUpdater(false) {}

void HospitalScreen::update()
{
    handleInput();

    if (IsKeyPressed(KEY_ENTER))
    {
        if (currentFocus == HOSPITAL_EMAIL_INPUT && !emailInput.empty())
        {
            currentFocus = HOSPITAL_PASSWORD_INPUT;
        }
        else if (currentFocus == HOSPITAL_PASSWORD_INPUT && !passwordInput.empty())
        {
            loginInProgress = true;
            loginSuccess = login(emailInput, passwordInput); // Check credentials from CSV
            loginSuccessChecker();
            loginInProgress = false;
        }
    }
}

void HospitalScreen::draw()
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
        DrawText("Invalid Email or Password", 50, 170, 20, RED);
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
            currentFocus = HOSPITAL_EMAIL_INPUT;
            loginInProgress = false;
            loginSuccess = false;
            invalidLoginUpdater = false;
        }
    }
}

void HospitalScreen::handleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (currentFocus == HOSPITAL_EMAIL_INPUT && !emailInput.empty())
        {
            emailInput.pop_back();
        }
        else if (currentFocus == HOSPITAL_PASSWORD_INPUT && !passwordInput.empty())
        {
            passwordInput.pop_back();
        }
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if (currentFocus == HOSPITAL_EMAIL_INPUT && emailInput.size() < 30)
        {
            emailInput += (char)key;
        }
        else if (currentFocus == HOSPITAL_PASSWORD_INPUT && passwordInput.size() < 20)
        {
            passwordInput += (char)key;
        }
        key = GetCharPressed();
    }
}

bool HospitalScreen::login(const string &inputEmail, const string &inputPassword)
{
    ifstream file("CSV_Files/hospital_info.csv");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open hospital data file!" << endl;
        return false;
    }

    string line, stored_hospital, stored_email, stored_password;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, stored_hospital, ',');
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

void HospitalScreen::loginSuccessChecker()
{
    if (!loginSuccess)
    {
        emailInput.clear();
        passwordInput.clear();
        currentFocus = HOSPITAL_EMAIL_INPUT;
        invalidLoginUpdater = true;
    }
    else
    {
        emailInput.clear();
        passwordInput.clear();
        currentFocus = HOSPITAL_EMAIL_INPUT;
        invalidLoginUpdater = false;
        currentScreen = POST_HOSPITAL_SCREEN;
        loginInProgress = false;
        loginSuccess = false;
    }
}
