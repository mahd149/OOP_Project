#ifndef POSTMODERATORSCREEN_H
#define POSTMODERATORSCREEN_H

#include "raylib.h"
#include <string>
#include "screen.h"

class PostModeratorScreen
{
private:
    Screen &currentScreen;
public:
    PostModeratorScreen(Screen &screen);
    void update();
    void draw();
};

#endif
