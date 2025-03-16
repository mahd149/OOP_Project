#include "../headers/adminRegistrationScreen.h"
#include "../headers/menu.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

AdminRegistrationScreen::AdminRegistrationScreen(Screen &screen)
    : currentScreen(screen), usernameInput(""), emailInput(""), passwordInput(""), registrationSuccess(false), currentFocus(0) {}

void AdminRegistrationScreen::update()
{
    handleInput();
}

void AdminRegistrationScreen::draw()
{
    ClearBackground(RAYWHITE);

    DrawText("Register New Admin", 50, 50, 24, BLACK);

    // Username input
    DrawText("Username:", 50, 120, 20, BLACK);
    if (currentFocus == 0)
        DrawRectangle(200, 115, 300, 30, LIGHTGRAY);
    else
        DrawRectangle(200, 115, 300, 30, GRAY);
    DrawText(usernameInput.c_str(), 210, 120, 20, BLACK);

    // Email input
    DrawText("Email:", 50, 180, 20, BLACK);
    if (currentFocus == 1)
        DrawRectangle(200, 175, 300, 30, LIGHTGRAY);
    else
        DrawRectangle(200, 175, 300, 30, GRAY);
    DrawText(emailInput.c_str(), 210, 180, 20, BLACK);

    // Password input
    DrawText("Password:", 50, 240, 20, BLACK);
    if (currentFocus == 2)
        DrawRectangle(200, 235, 300, 30, LIGHTGRAY);
    else
        DrawRectangle(200, 235, 300, 30, GRAY);
    DrawText(string(passwordInput.size(), '*').c_str(), 210, 240, 20, BLACK); // Mask password input

    // Register button
    DrawRectangle(50, 300, 150, 40, DARKGRAY);
    DrawText("Register", 80, 310, 20, WHITE);

    // Back button
    DrawRectangle(50, 400, 150, 40, LIGHTGRAY);
    DrawText("Back", 90, 410, 20, BLACK);

    // Success message
    if (registrationSuccess)
    {
        DrawText("Admin registered successfully!", 50, 350, 20, GREEN);
    }
}

void AdminRegistrationScreen::handleInput()
{
    // 0 = Username, 1 = Email, 2 = Password
    static bool invalidIdentifier = false;
    if (IsKeyPressed(KEY_TAB))
    {
        currentFocus = (currentFocus + 1) % 3;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (currentFocus == 0 && !usernameInput.empty())
        {
            usernameInput.pop_back();
        }
        else if (currentFocus == 1 && !emailInput.empty())
        {
            emailInput.pop_back();
        }
        else if (currentFocus == 2 && !passwordInput.empty())
        {
            passwordInput.pop_back();
        }
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if (currentFocus == 0 && usernameInput.size() < 20)
        {
            usernameInput += (char)key;
        }
        else if (currentFocus == 1 && emailInput.size() < 30)
        {
            emailInput += (char)key;
        }
        else if (currentFocus == 2 && passwordInput.size() < 20)
        {
            passwordInput += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER) && !passwordInput.empty() && !emailInput.empty() && !usernameInput.empty())
    {
        invalidIdentifier = false;
        registerAdmin();
    }
    else if (IsKeyPressed(KEY_ENTER) && !invalidIdentifier)
    {
        invalidIdentifier = true;
        registrationSuccess = false;
    }
    else if (invalidIdentifier)
    {
        DrawText("Invalid Username, Email or Password", 50, 350, 20, RED);
    }

    // Handle mouse clicks for buttons
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        // Register button click
        if (mouseX >= 50 && mouseX <= 200 && mouseY >= 300 && mouseY <= 340 && !passwordInput.empty() && !emailInput.empty() && !usernameInput.empty())
        {
            invalidIdentifier = false;
            registerAdmin();
        }
        else if (mouseX >= 50 && mouseX <= 200 && mouseY >= 300 && mouseY <= 340 && !invalidIdentifier)
        {
            invalidIdentifier = true;
            registrationSuccess = false;
        }
        

        // Back button click
        if (mouseX >= 50 && mouseX <= 200 && mouseY >= 400 && mouseY <= 440)
        {
            currentScreen = POST_LOGIN_SCREEN;
            currentFocus = 0;
            emailInput.clear();
            passwordInput.clear();
            usernameInput.clear();
        }
    }
}

void AdminRegistrationScreen::registerAdmin()
{
    ifstream file("CSV_Files/admin_data.csv");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open user data file!" << endl;
        return;
    }

    string line, stored_username, stored_email, stored_password;

    // Check if email already exists
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, stored_username, ',');
        getline(ss, stored_email, ',');
        getline(ss, stored_password, ',');

        if (stored_email == emailInput)
        {
            cerr << "Error: Email already exists!" << endl;
            file.close();
            return;
        }
    }

    file.close();

    // Open file in append mode to add a new user
    ofstream outfile("CSV_Files/admin_data.csv", ios::app);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open user data file for writing!" << endl;
        return;
    }

    // Write new user data to the file
    outfile << endl
            << usernameInput << "," << emailInput << "," << passwordInput;
    outfile.close();

    registrationSuccess = true;
    currentFocus = 0;
    // Clear input fields after registration
    usernameInput.clear();
    emailInput.clear();
    passwordInput.clear();
}
