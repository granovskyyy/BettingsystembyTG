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
    void blockUser(const string& username,int hours);
    bool unblockUser(const string& username);
    void processTimeStep(); //processing time steps for temporary blocks
};