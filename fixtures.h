#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "userprofile.h"
#include <algorithm>
#include <random>
using namespace std;

class Fixtures
{
    public:
    vector <string> SaveTeams(fstream &filename);
    vector <pair<string ,string>> Matchmaking(vector<string> teams);


};