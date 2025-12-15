#pragma once
#include <vector>
#include <string>
using namespace std;
class Database;
struct MatchEvent;
struct Bet
{
    int id;
    string username;
    string league;
    string team1;
    string team2;
    string bet_type;
    double odds;
    double stake;
    double poswin;
    string result;
    string status;
};
class BetSystem{
    Database& db;
    public:
    BetSystem(Database& database);
    bool newBet(const string& username, const MatchEvent& match, const string& league, const string& betType, double stake);
    vector <Bet> getUserBets(const string& username);
    string MatchPredictor();
    void resolveBets(const string& league);
    vector <Bet> pendingBets(const string& username);
    void resolveMatches(const string& league);
    void resolveLeague(const string& league);

};