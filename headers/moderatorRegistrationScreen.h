#ifndef MODERATOR_REGISTRATION_SCREEN_H
#define MODERATOR_REGISTRATION_SCREEN_H

#include "raylib.h"
#include "menu.h"
#include "screen.h"
#include <string>

class ModeratorRegistrationScreen
{
public:
    ModeratorRegistrationScreen(Screen &screen);
    void update();
    void draw();
    void handleInput();
    void registerModerator();

private:
    Screen &currentScreen;
    std::string usernameInput;
    std::string emailInput;
    std::string passwordInput;
    bool registrationSuccess;
    int currentFocus;
};

#endif
