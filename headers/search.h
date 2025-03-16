#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Search {
public:
    string trim(const string &str);
    void searchBlood(const string &bloodGroup, const string &zip, vector<string> &results);  // Updated declaration
};
