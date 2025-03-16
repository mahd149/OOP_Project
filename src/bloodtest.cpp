#include "../headers/bloodtest.h"

Bloodtest::Bloodtest(string bGroup, int qty, string hname)
    : bloodGroup(bGroup), quantity(qty), hospitalName(hname), isApproved(false) {}

bool Bloodtest::approveRequest()
{
    if (isApproved)
        return true;
    else
        return false;
}

string Bloodtest::getBloodGroup() { return bloodGroup; }
int Bloodtest::getQuantity() { return quantity; }
bool Bloodtest::initial_test()
{
    srand(time(0));
    cout << "Performing **Initial Blood Safety Tests** before adding to inventory...\n";

    bool bloodTyping = rand() % 10;
    bool infectionScreening = rand() % 10;
    bool hemoglobinLevel = rand() % 10;

    if (bloodTyping)
    {
        cout << "Blood Typing (ABO & Rh): Passed\n";
        bloodTypingString.push_back("Blood Typing (ABO & Rh): Passed");
    }
    else
    {
        cout << "Blood Typing (ABO & Rh): Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        bloodTypingString.push_back("Blood Typing (ABO & Rh): Failed. **Blood is NOT safe for storage!**\n");
        return false;
    }

    if (infectionScreening)
    {
        cout << "Infection Screening: Passed\n";
        infectionScreeningString.push_back("Infection Screening: Passed");
    }
    else
    {
        cout << "Infection Screening: Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        infectionScreeningString.push_back("Infection Screening: Failed. **Blood is NOT safe for storage!**");
        return false;
    }

    if (hemoglobinLevel)
    {
        cout << "Hemoglobin Level: Passed\n";
        hemoglobinLevelString.push_back("Hemoglobin Level: Passed");
    }
    else
    {
        cout << "Hemoglobin Level: Failed\n";
        cout << "**Blood is NOT safe for storage!**\n";
        hemoglobinLevelString.push_back("Hemoglobin Level: Failed. **Blood is NOT safe for storage!**");
        return false;
    }
    cout << "**All tests passed! Blood is safe for storage.**\n";
    cout << "asdsda" << endl;
    return true;
}

vector<string> Bloodtest::getBloodTypingResults() const {
    return bloodTypingString;
}

vector<string> Bloodtest::getInfectionScreeningResults() const {
    return infectionScreeningString;
}

vector<string> Bloodtest::getHemoglobinLevelResults() const {
    return hemoglobinLevelString;
}
