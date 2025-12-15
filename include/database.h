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
    bool MatchDay(string league); //checks if there are matches for the league
    void addMatch(const MatchEvent& m, string league); //adding matches to DB
    vector <MatchEvent> getMatches(string league); //getting matches' data from DB
    bool addBet(const Bet& bet); //adding bets to DB
    vector <Bet> getUserBets(const string& username); //getting bets of a user
    bool updateBetStatus(int betID,const string& status); //updating bet status
    bool updateBetResult(int betID, const string& result);//updating bet result
    vector <Bet> getPendingBets(const string& league); //getting pending bets for a league
    bool updateMatchResult(int matchID, const string& result); //updating match result
    vector <MatchEvent> getMatchesID(const string& league); //getting matches by ID
    //getters of data from columns 
    int getIntValue(const string& table, const string& column, const string& username); 
    double getDoubleValue(const string& table, const string& column, const string& username);
    string getStringValue(const string& table, const string& column, const string& username);
    //updating fields
    bool updateIntValue(const string& username, const string& column, int value);
    bool updateDoubleValue(const string& username, const string& column, double value);
    bool updateStringValue(const string& username, const string& column, const string& value);
    bool incrementBets(const string& username); //increment bet counter
    bool updateWithdrawalLimit(const string& username, double limit);   //update withdrawal limit
    double getWithdrawalLimit(const string& username); //get withdrawal limit
    bool incrementLockedDays();     //simulaton of user locking
    bool unlockUsers(); //unlocking users after lock period
    string getPasswordHash(const string& username);   //getting hashed password  
    bool updatePassword(const string& username, const string& newHashedPwd); //changing password 
};   
