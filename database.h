#pragma once 
#include "sqlite3.h"
#include <string>
using namespace std;

class Database{
    sqlite3* db;
    public: 
    Database(const string& filename);
    ~Database();

    bool addUser(const string& username, const string& pwd,double balance);
    bool getUser(const string& username, string& pwdOut,double& balanceout);
    bool updateBalance(const string& username, double newBalance);
};