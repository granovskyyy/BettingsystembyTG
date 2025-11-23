#pragma once 
#include "sqlite3.h"
#include <string>
#include "fixtures.h"
#include "betsystem.h"
using namespace std;
struct Bet;
struct MatchEvent;
class Database{
    sqlite3* db;
    public: 
    Database(const string& filename);
    ~Database();

    bool addUser(const string& username, const string& pwd,double balance); //adding users to database
    bool getUser(const string& username, string& pwdOut,double& balanceout); //getting users' data
    bool updateBalance(const string& username, double newBalance);//updating users balance
    bool MatchDay(string league); 
    void addMatch(const MatchEvent& m, string league); //adding matches to DB
    vector <MatchEvent> getMatches(string league); //getting matches' data from DB
    bool addBet(const Bet& bet); //adding bets to DB
    vector <Bet> getUserBets(const string& username);
    bool updateBetStatus(int betID,const string& status);
    bool updateBetResult(int betID, const string& result);
    vector <Bet> getPendingBets(const string& league);
    bool updateMatchResult(int matchID, const string& result);
    vector <MatchEvent> getMatchesID(const string& league);
    
};