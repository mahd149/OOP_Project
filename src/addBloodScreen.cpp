#include "../headers/addBloodScreen.h"
#include "raylib.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

AddBloodScreen::AddBloodScreen(Screen &screen, Hospital &hospital)
    : currentScreen(screen), hospital(hospital), donorIDInput(""), invalid(false), newDonorName(""), donorID(-1), bloodGroup(""), zipCode(""), age(""), contact(""), bagsOfBlood("") {}

bool isValidInteger(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
            return false; 
    }
    return true; 
}

void AddBloodScreen::update()
{
    if (IsKeyPressed(KEY_BACKSPACE) && !donorIDInput.empty())
    {
        donorIDInput.pop_back();
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if (donorIDInput.length() < 25)
        {
            donorIDInput += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 0)
    {
        if (donorIDInput != "-1")
        {
            messages.clear();
            donorID = atoi(donorIDInput.c_str());
            donorIDInput.clear();
            vector<string> result = hospital.addBlood(donorID);
            
            if (!result.empty())
            {
                invalid = false;
                int fieldIndex = 0;
                string segment;

                for (const string &msg : result)
                {
                    for (char ch : msg)
                    {
                        if (ch == '.')
                        {
                            if (!segment.empty())
                            {
                                switch (fieldIndex)
                                {
                                case 0:
                                    newDonorName = segment;
                                    break;
                                case 1:
                                    bloodGroup = segment;
                                    break;
                                case 2:
                                    age = segment;
                                    break;
                                case 3:
                                    zipCode = segment;
                                    break;
                                case 4:
                                    contact = segment;
                                    break;
                                }
                                segment.clear(); // Reset for the next value
                                fieldIndex++;    // Move to the next field
                            }
                        }
                        else
                        {
                            segment += ch;
                        }
                    }
                }

                // Store the last remaining segment if any
                if (!segment.empty())
                {
                    switch (fieldIndex)
                    {
                    case 0:
                        newDonorName = segment;
                        break;
                    case 1:
                        bloodGroup = segment;
                        break;
                    case 2:
                        age = segment;
                        break;
                    case 3:
                        zipCode = segment;
                        break;
                    case 4:
                        contact = segment;
                        break;
                    }
                }

                commandShifter = 7;
                additionalCommand = NON_NEW;
                BSCommand = VALID;
            }
            else
                invalid = true;
        }

        else if (donorIDInput == "-1")
        {
            commandShifter = 2;
            vector<string> result = hospital.addBlood(donorID);
            messages.insert(messages.end(), result.begin(), result.end());
            invalid = false;
            additionalCommand = NEW;
            flushInput();
        }
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 2)
    {
        commandShifter++;
        cout << "Command Shifter = " << commandShifter << endl;
        newDonorName = donorIDInput;
        cout << "New Donor Name: " << newDonorName << endl;
        flushInput();
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 3)
    {
        bloodGroup = donorIDInput;
        bloodGroup = hospital.normalizeBloodGroup(bloodGroup);
        if (bloodGroup.empty())
        {
            BSCommand = INVALID_BLOOD;
            donorIDInput.clear();
            return;
        }
        BSCommand = VALID;
        commandShifter++;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Command Shifter = " << commandShifter << endl;
        flushInput();
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 5)
    {
        zipCode = donorIDInput;
        if (isValidInteger(zipCode))
        {
            int numZip = stoi(zipCode);
            if (numZip < 0 || numZip > 9999)
            {
                donorIDInput.clear();
                BSCommand = INVALID_ZIP_CODE;
                return;
            }
        }
        else
        {
            BSCommand = INVALID_ZIP_CODE;
            donorIDInput.clear();
            return;
        }
        BSCommand = VALID;
        commandShifter++;
        cout << "Zip Code: " << zipCode << endl;
        cout << "Command Shifter = " << commandShifter << endl;
        flushInput();
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 4)
    {
        age = donorIDInput;
        if (isValidInteger(age))
        {
            int numAge = stoi(age);
            cout << "numAge = " << numAge << endl;
            if (numAge < 18 || numAge > 150)
            {
                donorIDInput.clear();
                BSCommand = INVALID_AGE;
                return;
            }
        }
        else
        {
            donorIDInput.clear();
            BSCommand = INVALID_AGE;
            return;
        }
        BSCommand = VALID;
        commandShifter++;
        cout << "Command Shifter = " << commandShifter << endl;
        flushInput();
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 6)
    {

        if (donorIDInput.length() == 11 && all_of(donorIDInput.begin(), donorIDInput.end(), ::isdigit))
        {
            contact = donorIDInput;
            BSCommand = VALID;
        commandShifter++;
            cout << "Contact: " << contact << endl;
            cout << "Command Shifter = " << commandShifter << endl;
            flushInput();
        }
        else
        {
            cout << "Invalid Contact." << endl;
            BSCommand = INVALID_CONTACT;
            donorIDInput.clear();
        }
    }
    else if (IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && commandShifter == 7 && BSCommand != INVALID_BLOOD_REGISTRATION_TIME && BSCommand != INVALID_BLOOD_TEST)
    {
        bagsOfBlood = donorIDInput;
        int no;
        if (isValidInteger(bagsOfBlood))
        {
            no = stoi(bagsOfBlood.c_str());
            donorIDInput.clear();
            if (no <= 0 || no > 3)
            {
                BSCommand = INVALID_BLOOD_NO;
                return;
            }
        }
        else
        {
            donorIDInput.clear();
            BSCommand = INVALID_BLOOD_NO;
            return;
        }
        ///
        bloodyTimeTrackerResult = hospital.bloodyTimeTracker();
        if (!bloodyTimeTrackerResult.empty())
        {
            donorIDInput.clear();
            cout << "Time problem" << endl;
            BSCommand = INVALID_BLOOD_REGISTRATION_TIME;
            commandShifter = 9;
            return;
        }
        ////
        if (hospital.bloodyTester(bloodGroup, no))
        {
            cout << "Passed" << endl;
        }
        else
        {
            cout << "Failed" << endl;
            BSCommand = INVALID_BLOOD_TEST;
            return;
        }

        BSCommand = VALID;
        commandShifter++;
        cout << "Last ID = " << Hospital::getLastId() << endl;
        ///
        int newDonorID = Hospital::getLastId() + 1;
        Donor d(newDonorID, newDonorName, bloodGroup, stoi(age), stoi(zipCode), contact);
        stringstream newRecord;
        newRecord << newDonorID << "," << newDonorName << "," << bloodGroup << "," << age << "," << zipCode << "," << contact << ",0";
        vector<string> donorRecords;
        donorRecords.push_back(newRecord.str());
        ///

        hospital.write_to_inventory(no, bloodGroup);
        if (additionalCommand == NEW)
            hospital.write_details(no, d, donorRecords);
        else
            hospital.write_details(no, d, donorRecords, donorID);
    }
    else if (commandShifter == 8 && IsKeyPressed(KEY_ENTER) && donorIDInput == "-1")
    {
        ExitScreenCommand();
    }
    else if (commandShifter == 9 && IsKeyPressed(KEY_ENTER) && donorIDInput == "-1")
    {
        ExitScreenCommand();
    }
    else if ((commandShifter == 9 || commandShifter == 8) && IsKeyPressed(KEY_ENTER) && !donorIDInput.empty() && donorIDInput != "-1")
    {
        donorIDInput.clear();
    }
}

void AddBloodScreen::draw()
{
    //////////////
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    bool isMouseOverButton = (mouseX >= 50 && mouseX <= 350) && (mouseY >= 500 && mouseY <= 540); // Check if mouse is within button bounds

    if (isMouseOverButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // If mouse is over the button and clicked
    {
        ExitScreenCommand();
    }
    /////////////////

    ClearBackground(RAYWHITE);

    if (commandShifter == 0)
        DrawText("Enter Donor ID (Press -1 to add new Donor):", 50, 50, 24, BLACK);
    else if (commandShifter == 1)
        DrawText("Enter Command:", 50, 50, 24, BLACK);
    else if (commandShifter == 2)
    {
        DrawText("Enter Donor Name:", 50, 50, 24, BLACK);
    }
    else if (commandShifter == 3)
    {
        DrawText("Enter Blood Group: ", 50, 50, 24, BLACK);
    }
    else if (commandShifter == 5)
    {
        DrawText("Enter Zip Code: ", 50, 50, 24, BLACK);
    }
    else if (commandShifter == 4)
    {
        DrawText("Enter Age (18 - 150): ", 50, 50, 24, BLACK);
    }
    else if (commandShifter == 6)
    {
        DrawText("Enter Contact:", 50, 50, 24, BLACK);
    }
    else if (commandShifter == 7 || commandShifter == 8)
    {
        if (BSCommand != INVALID_BLOOD_REGISTRATION_TIME && BSCommand != INVALID_BLOOD_TEST && commandShifter != 8)
            DrawText("Enter number of bags of blood to take (Max 3): ", 50, 50, 24, BLACK);
        int yOffset = 160;
        DrawText(("Donor Name: " + newDonorName).c_str(), 50, yOffset, 24, BLACK);

        if (additionalCommand != NON_NEW)
        {
            int textWidth = MeasureText(("Donor Name: " + newDonorName).c_str(), 24);

            DrawText(" (NEW)", 50 + textWidth, yOffset, 24, RED);

            DrawText(" (NEW)", 52 + textWidth, yOffset - 2, 24, Fade(RED, 0.6f));
        }
        yOffset += 40;
        DrawText(("Blood Group: " + bloodGroup).c_str(), 50, yOffset, 20, DARKGRAY);
        yOffset += 30;

        DrawText(("Contact: " + contact).c_str(), 50, yOffset, 20, DARKGRAY);
        yOffset += 30;

        DrawText(("Zip Code: " + zipCode).c_str(), 50, yOffset, 20, DARKGRAY);
        yOffset += 30;
        if (BSCommand == INVALID_BLOOD_NO)
            DrawText("Invalid. You can only donate 1, 2, or 3 bags. Please try again.", 50, yOffset, 20, RED);
    }
    if (BSCommand == INVALID_BLOOD_TEST || commandShifter == 8)
    {
        int yOffset = 300;

        DrawText("Press -1 or click 'Back to main menu'", 50, 50, 24, BLACK);
        DrawText("Performing 'Initial Blood Safety Tests': ", 50, yOffset, 24, DARKBLUE);
        yOffset += 30; // Move down for test results

        for (const string &result : bloodTypingResult)
        {
            DrawText(result.c_str(), 50, yOffset, 20, BLACK);
            yOffset += 25; // Adjust spacing between lines
        }

        for (const string &result : infectionScreeningResults)
        {
            DrawText(result.c_str(), 50, yOffset, 20, BLACK);
            yOffset += 25;
        }
        for (const string &result : hemoglobinLevelResults)
        {
            DrawText(result.c_str(), 50, yOffset, 20, BLACK);
            yOffset += 25;
        }
        if (BSCommand != INVALID_BLOOD_TEST)
        {
            DrawText("All tests passed! Blood is safe for storage.", 50, yOffset, 22, DARKBLUE);
            yOffset += 25;
            vector<string> fin;
            fin.push_back("Successfully added " + bagsOfBlood + " bags to " + bloodGroup + "blood group.");
            for (const string &result : fin)
            {
                DrawText(result.c_str(), 50, yOffset, 20, DARKBLUE);
                yOffset += 25;
            }
        }
        else if (BSCommand == INVALID_BLOOD_TEST)
        {
            commandShifter = 8;
            DrawText("Test failed. Blood is not safe for storage.", 50, yOffset, 22, RED);
            yOffset += 25;
        }
    }

    DrawRectangle(50, 100, 300, 40, LIGHTGRAY);
    DrawText(donorIDInput.c_str(), 60, 110, 24, BLACK);

    if (invalid)
        DrawText("INVALID ID", 40, 220, 20, RED);
    else if (BSCommand == INVALID_BLOOD)
        DrawText("Invalid blood group. Please enter (A+, A-, B+, B-, AB+, AB-, O+, O-).", 50, 220, 20, RED);
    else if (BSCommand == INVALID_AGE)
        DrawText("Invalid Age. Enter a number between 18 and 150.", 50, 220, 20, RED);
    else if (BSCommand == INVALID_ZIP_CODE)
        DrawText("Invalid Zip Code. Enter a number between 0 and 9999.", 50, 220, 20, RED);
    else if (BSCommand == INVALID_CONTACT)
        DrawText("Invalid Contact. Must be exactly 11 digits.", 50, 220, 20, RED);
    else if (BSCommand == INVALID_BLOOD_REGISTRATION_TIME)
    {
        for (const auto &text : bloodyTimeTrackerResult)
        {
            DrawText(text.c_str(), 50, 160, 24, RED);
        }
        DrawText("Press -1 or click 'Back to main menu'", 50, 50, 24, BLACK);
    }

    // int yOffset = 170;

    /*  for (const auto &message : messages)
     {
         string segment;
         for (char ch : message)
         {
             if (ch == '.')
             {
                 if (!segment.empty())
                 {
                     DrawText(segment.c_str(), 50, yOffset, 24, DARKGRAY);
                     yOffset += 30;
                     segment.clear();
                 }
             }
             else
             {
                 segment += ch;
             }
         }


         if (!segment.empty())
         {
             DrawText(segment.c_str(), 50, yOffset, 24, DARKGRAY);
             yOffset += 30;
         }
     } */

    DrawRectangle(50, 500, 300, 40, DARKGRAY);
    DrawText("Back to Hospital Menu", 60, 510, 20, WHITE);
}

void AddBloodScreen::flushInput()
{
    // messages.clear();
    donorIDInput.clear();
}

void AddBloodScreen::ExitScreenCommand()
{
    currentScreen = POST_HOSPITAL_SCREEN;
    commandShifter = 0;
    flushInput();
    additionalCommand = NEW;
    BSCommand = VALID;
}
