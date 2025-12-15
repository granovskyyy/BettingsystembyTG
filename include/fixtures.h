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

struct MatchEvent //structure for a match event 
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
    vector <string> SaveTeams(fstream &filename); //saving teams from a file
    vector <MatchEvent> Matchmaking(vector<string> teams); //creating matches from teams
    MatchEvent createMatch(const string& t1, const string& t2); //creating a single match event
    

};