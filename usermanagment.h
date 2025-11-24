#pragma once
#include "database.h"
using namespace std;
class UserManagment{
    Database& db;
    public:
    UserManagment(Database& database);
    bool canPlaceBet(const string& username);
    void registerBet(const string& username);
    double getWithdrawalLimit(const string& username);
    bool updateWithdrawalLimit(const string& username, double newLimit);
    void resetDailyLimit(const string& username);
    bool isBlocked(const string& username);
    bool blockUser(const string& username);
    bool unblockUser(const string& username);

};