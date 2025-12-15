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
    bool newBet(const string& username, const MatchEvent& match, const string& league, const string& betType, double stake); //placing new bet
    vector <Bet> getUserBets(const string& username); //getting user bets
    string MatchPredictor(); //predicting match outcome
    void resolveBets(const string& league); //resolving bets for a league
    vector <Bet> pendingBets(const string& username); //getting pending bets for user
    void resolveMatches(const string& league); //resolving matches for a league
    void resolveLeague(const string& league); //resolving all bets and matches for a league

};