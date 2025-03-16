#ifndef FILE_OPTIONS_SCREEN_H
#define FILE_OPTIONS_SCREEN_H

#include "raylib.h"
#include "menu.h"
#include "screen.h"

void openCSVFile(const std::string &fileName);
class FileOptionsScreen {
public:
    FileOptionsScreen(Screen &screen);
    void update();
    void draw();
    void handleInput();

private:
    Screen &currentScreen;
    int selectedOption;
};

#endif
