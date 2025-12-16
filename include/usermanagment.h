#pragma once
#include "database.h"


using namespace std;

class UserManagment{
    Database& db;
    public:
    UserManagment(Database& database);
    bool isBlocked(const string& username);//account bloking
    void blockUser(const string& username,int hours); //blocking user
    bool unblockUser(const string& username); //unblocking user
    void processTimeStep(); //processing time steps for temporary blocks
};