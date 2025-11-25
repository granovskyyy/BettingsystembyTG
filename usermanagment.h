#pragma once
#include "database.h"
using namespace std;
class UserManagment{
    Database& db;
    public:
    UserManagment(Database& database);
    bool canPlaceBet(const string& username); //limts
    void registerBet(const string& username);

    void resetDailyLimit(const string& username);//reset limits
    bool isBlocked(const string& username);//account bloking
    bool blockUser(const string& username);
    bool unblockUser(const string& username);
    bool selfExclude(const string& username, int days); //hiding account
    bool isSelfExcluded(const string& username);

};