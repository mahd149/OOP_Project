#ifndef ADD_BLOOD_SCREEN_H
#define ADD_BLOOD_SCREEN_H

#include "screen.h"
#include "donor.h"
#include "../headers/hospital.h"
#include "surgical.h"
#include "bloodtest.h"
#include <string>
#include <vector>

using namespace std;

enum AddBloodScreenCommand
{
    INVALID_BLOOD,
    VALID,
    INVALID_AGE,
    INVALID_ZIP_CODE,
    INVALID_CONTACT,
    INVALID_BLOOD_NO,
    INVALID_BLOOD_REGISTRATION_TIME,
    INVALID_BLOOD_TEST
};

enum AddBloodScreenAdditionalCommand
{
    NON_NEW,
    NEW,
};

class AddBloodScreen : public Hospital
{
private:
    Screen &currentScreen;
    Hospital &hospital;
    string donorIDInput;
    vector<string> messages; // To display messages from addBlood()
    int donorInputStep = 0;  // Track the input field (0: name, 1: blood group, etc.)
    string donorInput;
    Donor newDonor;
    bool invalid;
    AddBloodScreenCommand BSCommand = VALID;
    AddBloodScreenAdditionalCommand additionalCommand = NEW;
    string newDonorName;
    int donorID;
    string bloodGroup;
    string zipCode;
    string age;
    string contact;
    string bagsOfBlood;
    vector<string> bloodyTimeTrackerResult;
    int commandShifter = 0;

public:
    AddBloodScreen(Screen &screen, Hospital &hospital);
    void flushInput();
    void update();
    void draw();
    void receiveTestResults(Bloodtest *test);
    void ExitScreenCommand();
};

#endif
