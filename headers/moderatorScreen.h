#ifndef MODERATORSCREEN_H
#define MODERATORSCREEN_H

#include "raylib.h"
#include <string>
#include "screen.h"

enum InputFocusModeratorScreen
{
    MODERATOR_EMAIL_INPUT,
    MODERATOR_PASSWORD_INPUT
};

class ModeratorScreen
{
private:
    std::string emailInput;
    std::string passwordInput;
    bool loginInProgress;
    bool loginSuccess;
    Screen &currentScreen;
    InputFocusModeratorScreen currentFocus;
    bool invalidLoginUpdater;

public:
    ModeratorScreen(Screen &screen);
    void update();
    void draw();
    void loginSuccessChecker();
    void handleInput();
    bool login(const std::string &inputEmail, const std::string &inputPassword);
};

#endif
