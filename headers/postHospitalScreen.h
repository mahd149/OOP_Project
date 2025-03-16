#ifndef POSTHOSPITALSCREEN_H
#define POSTHOSPITALSCREEN_H

#include "screen.h"
#include "raylib.h"

class PostHospitalScreen
{
private:
    Screen &currentScreen;

public:
    PostHospitalScreen(Screen &screen);
    void update();
    void draw();
};

#endif
