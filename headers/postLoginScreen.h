#ifndef POST_LOGIN_SCREEN_H
#define POST_LOGIN_SCREEN_H

#include "raylib.h"
#include "menu.h"
#include "screen.h"

class PostLoginScreen
{
public:
    PostLoginScreen(Screen &screen);
    void update();
    void draw();
    void handleInput();

private:
    Screen &currentScreen;
};

#endif