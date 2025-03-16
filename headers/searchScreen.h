#ifndef SEARCHSCREEN_H
#define SEARCHSCREEN_H

#include "raylib.h"
#include <vector>
#include <string>
#include "search.h"
#include "screen.h"

using namespace std;

enum InputFocus
{
    BLOOD_GROUP_INPUT,
    ZIP_CODE_INPUT
};

class SearchScreen
{
private:
    bool searchInProgress;
    vector<string> searchResults;
    string bloodGroupInput;
    string zipInput;
    Search search; 
    Screen &currentScreen;
    InputFocus currentFocus;
    bool clearinput;

public:
    SearchScreen(Screen &screen); 
    void update();  
    void draw();  
    void handleInput(); 
    void searchForBlood(); 
};

#endif
