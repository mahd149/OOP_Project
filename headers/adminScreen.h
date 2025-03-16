#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include "raylib.h"
#include <string>
#include "screen.h"

enum InputFocusAdminScreen
{
    EMAIL_INPUT,
    PASSWORD_INPUT
};

class AdminScreen
{
private:
    std::string emailInput;
    std::string passwordInput;
    bool loginInProgress;
    bool loginSuccess;
    Screen &currentScreen;
    InputFocusAdminScreen currentFocus;
    bool invalidLoginUpdater;
public:
    AdminScreen(Screen &screen);
    void update();
    void draw();
    void loginSuccessChecker();
    void handleInput();
    bool login(const std::string &inputEmail, const std::string &inputPassword);
};

#endif
