#ifndef ADMIN_REGISTRATION_SCREEN_H
#define ADMIN_REGISTRATION_SCREEN_H

#include "raylib.h"
#include "menu.h"
#include "screen.h"
#include <string>

class AdminRegistrationScreen {
public:
    AdminRegistrationScreen(Screen &screen);
    void update();
    void draw();
    void handleInput();
    void registerAdmin();

private:
    Screen &currentScreen;
    std::string usernameInput;
    std::string emailInput;
    std::string passwordInput;
    bool registrationSuccess;
    int currentFocus;
};

#endif
