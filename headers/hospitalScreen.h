#ifndef HOSPITALSCREEN_H
#define HOSPITALSCREEN_H

#include "raylib.h"
#include <string>
#include "screen.h"

enum InputFocusHospitalScreen
{
    HOSPITAL_EMAIL_INPUT,
    HOSPITAL_PASSWORD_INPUT
};

class HospitalScreen
{
private:
    std::string emailInput;
    std::string passwordInput;
    bool loginInProgress;
    bool loginSuccess;
    Screen &currentScreen;
    InputFocusHospitalScreen currentFocus;
    bool invalidLoginUpdater;

public:
    HospitalScreen(Screen &screen);
    void update();
    void draw();
    void loginSuccessChecker();
    void handleInput();
    bool login(const std::string &inputEmail, const std::string &inputPassword);
};

#endif
