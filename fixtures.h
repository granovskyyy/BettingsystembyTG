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

struct MatchEvent
{
    int id;
    string team1;
    string team2;
    double odds1;
    double oddsX;
    double odds2;
    string result;
};
class Fixtures
{
    public:
    vector <string> SaveTeams(fstream &filename);
    vector <MatchEvent> Matchmaking(vector<string> teams);
    MatchEvent createMatch(const string& t1, const string& t2);
    

};