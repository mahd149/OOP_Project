#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <iostream>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;

enum MenuOption
{
    SEARCH_BLOOD,
    ADMIN_LOGIN,
    MODERATOR_LOGIN,
    HOSPITAL_LOGIN,
    EXIT,
    NONE
};

class Menu
{
public:
    virtual void drawMenu(bool isMainMenu) = 0;  // Update to accept 'isMainMenu' argument
    virtual MenuOption handleButtonClick(int mouseX, int mouseY) = 0;
};

class MainMenu : public Menu
{
private:
    Texture2D bgImage;
    Rectangle buttons[5];
    const char *labels[5];
    bool hovered[5];
public:
    MainMenu();
    ~MainMenu();
    void drawMenu(bool isMainMenu) override;  // Update to match the new definition
    MenuOption handleButtonClick(int mouseX, int mouseY) override;
};

#endif
